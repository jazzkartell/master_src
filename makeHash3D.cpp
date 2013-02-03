#include <string>
#include <iostream>
#include <pcl/point_types.h>
#include "Utils.h"
#include "pcl/common/geometry.h"
#include "pcl/common/transformation_from_correspondences.h"
#include "pcl/common/transforms.h"
#include "pcl/common/distances.h"

using namespace std;

POINT_CLOUD_REGISTER_POINT_STRUCT(Point3D,(float, x, x)(float, y, y)(float, z, z)(u_int32_t, label_id, label_id)(u_int32_t, model_id, model_id))

vector<string> labels;
// a basis consists of three points, so we use a vector
vector<vector<int> > models;


int main(int argc, char** argv) {
    
    pcl::PointCloud<Point3D>::Ptr cloud (new pcl::PointCloud<Point3D>);
    
    // we require one file containing the coordinate file as input
    if(argc != 2){
        cout << "Input File required!" << endl;
    }else{
        readFile(argv[1], cloud, labels);
    }
    
    // target point cloud
    pcl::PointCloud<Point3D>::Ptr cloud2 (new pcl::PointCloud<Point3D>);
    // get all possible basis pairs
    int basis_count = 0;
    
    for(int i=0; i<cloud->size(); i++){
        for (int j=0; j<cloud->size(); j++){
        	for (int k=0; k<cloud->size();k++){
            	if(i != j && i != k && j != k){
            		vector<int> m;
            		m.push_back(i);
            		m.push_back(j);
            		m.push_back(k);
                	models.push_back(m);
                	
                    Eigen::Vector3f a = Eigen::Vector3f(cloud->at(i).getArray3fMap());
                    Eigen::Vector3f b = Eigen::Vector3f(cloud->at(j).getArray3fMap());
                    Eigen::Vector3f c = Eigen::Vector3f(cloud->at(k).getArray3fMap());
                    
                    double a_length = pcl::geometry::distance(b,c);
                    double b_length = pcl::geometry::distance(a,c);
                    double c_length = pcl::geometry::distance(a,b);

                    // compute the heights of c to get z coordinate
					double z;
					double tmp = ((pow((pow(c_length,2)+pow(b_length,2)-pow(a_length,2)),2))/(4*pow(c_length,2)));
					if (pow(b_length,2)-tmp < 0){
                    	z = 0-sqrt(fabs(pow(b_length,2)-tmp));
					}else{
						z = sqrt(fabs(pow(b_length,2)-tmp));
					}
                    pcl::PointCloud<Point3D>::Ptr transformedCloud_tmp (new pcl::PointCloud<Point3D>);
                    pcl::PointCloud<Point3D>::Ptr transformedCloud (new pcl::PointCloud<Point3D>);

                	Eigen::Affine3f trans;
                	pcl::TransformationFromCorrespondences t;
                	
                    // map p1 to (0,0,0)
                	// point to get x line, x line goes directly to p2
                	t.add(a,Eigen::Vector3f(0.0,0.0,0.0),1.0);
                	t.add(b,Eigen::Vector3f(pcl::geometry::distance(a,b),0.0,0.0),1.0);
                	// now transform such that p1 and p2 build x-axes
                	trans = t.getTransformation();
                	pcl::transformPointCloud(*cloud, *transformedCloud_tmp, trans);
                    
                    Eigen::Affine3f trans2;
                	pcl::TransformationFromCorrespondences t2;
                    
                    Eigen::Vector3f new_c = Eigen::Vector3f(transformedCloud_tmp->at(k).getArray3fMap());
                    new_c[1] = 0.0;
                    new_c[2] = z;
                    
                    t2.add(transformedCloud_tmp->at(i).getArray3fMap(),transformedCloud_tmp->at(i).getArray3fMap(),1.0);
                	t2.add(transformedCloud_tmp->at(j).getArray3fMap(),transformedCloud_tmp->at(j).getArray3fMap(),1.0);
                    t2.add(transformedCloud_tmp->at(k).getArray3fMap(),new_c);
                    
                    trans2 = t2.getTransformation();
                	pcl::transformPointCloud(*transformedCloud_tmp, *transformedCloud, trans2);
                    
                	//check distances
                    //cout << "p1 -- p2 original: " << pcl::geometry::distance(cloud->at(i).getArray3fMap(),cloud->at(j).getArray3fMap()) << endl;
                    //cout << "p1 -- p3 original: " << pcl::geometry::distance(cloud->at(i).getArray3fMap(),cloud->at(k).getArray3fMap()) << endl;
                    //cout << "p2 -- p3 original: " << pcl::geometry::distance(cloud->at(j).getArray3fMap(),cloud->at(k).getArray3fMap()) << endl;
                    //cout << "p1 -- p2 transformed: " << pcl::geometry::distance(transformedCloud->at(i).getArray3fMap(),transformedCloud->at(j).getArray3fMap()) << endl;
                    //cout << "p1 -- p3 transformed: " << pcl::geometry::distance(transformedCloud->at(i).getArray3fMap(),transformedCloud->at(k).getArray3fMap()) << endl;
                    //cout << "p2 -- p3 transformed: " << pcl::geometry::distance(transformedCloud->at(j).getArray3fMap(),transformedCloud->at(k).getArray3fMap()) << endl << endl;
                    // set the model
                   
                	for (int k=0; k<transformedCloud->size(); k++){
                    	transformedCloud->at(k).model_id = basis_count;
                	}
                	basis_count++;
                	*cloud2 += *transformedCloud;
            	}
            }
        }
    }
    
    // put everything in a kd tree
    // pcl::search::KdTree<pcl::PointXYZL>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZL>);
    // tree->setInputCloud(cloud2);
    
    
    //string outFile = argv[1];

    /**prepare out file
    //prepare out file
    size_t result = outFile.find_last_of('.');

    if (string::npos != result){
        outFile.erase(result);
    }
    outFile.append("_hash.dat");
	**/
    printCloud(cloud2, labels, models);
    return 0;
}
