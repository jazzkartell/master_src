//#include "Utils.h"
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
                	pcl::PointCloud<Point3D>::Ptr transformedCloud (new pcl::PointCloud<Point3D>);
                	// transform cloud to every new coordinate frame
                	Eigen::Affine3f trans;
                	pcl::TransformationFromCorrespondences t;
                	// (0,0,0)
                	Eigen::Vector3f origin = Eigen::Vector3f(cloud->at(i).getArray3fMap());
                	// point to get x line
                	Eigen::Vector3f p2 = Eigen::Vector3f(cloud->at(j).getArray3fMap());
                	// map origin to 0,0,0 and p2 to (dist,0,0)
                	t.add(origin,Eigen::Vector3f(0.0,0.0,0.0),1.0);
                	t.add(p2,Eigen::Vector3f(pcl::geometry::distance(origin,p2),0.0,0.0),1.0);
                	trans = t.getTransformation();
                	//Transform all other points
                	pcl::transformPointCloud(*cloud, *transformedCloud, trans);
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
    
    //prepare out file
    string outFile = argv[1];
    size_t result = outFile.find_last_of('.');

    if (string::npos != result){
        outFile.erase(result);
    }
    outFile.append("_hash.dat");

    printCloud(cloud2, labels, models, outFile.c_str());
    return 0;
}

