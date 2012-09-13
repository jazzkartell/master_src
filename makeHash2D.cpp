//#include "Utils.h"
#include <string>
#include <iostream>
#include <pcl/point_types.h>
#include "Utils.h"
#include "pcl/common/geometry.h"
#include "pcl/common/transformation_from_correspondences.h"
#include "pcl/common/transforms.h"


using namespace std;



int main(int argc, char** argv) {
    
    pcl::PointCloud<pcl::PointXYZL>* cloud = new pcl::PointCloud<pcl::PointXYZL>();
    
    // we require one file containing the coordinate file as input
    if(argc != 2){
        cout << "Input File required!" << endl;
    }else{
        readFile(argv[1], cloud);
    }
    
    // get all possible basis pairs
    int basis_count = 0;
    for(int i=0; i<cloud->size(); i++){
        for (int j=0; j<cloud->size(); j++){
            if(i != j){
                basis_count++;
                
            }
        }
    }
    cout << basis_count << " basis were produced..." << endl;

    
    const Eigen::Vector3f y_dir = Eigen::Vector3f(0.0,1.0,0.0);
    const Eigen::Vector3f z_axis = Eigen::Vector3f(0.0,0.0,1.0);
    const Eigen::Vector3f origin = Eigen::Vector3f(2.0,3.0,0.0);
    
    pcl::PointCloud<pcl::PointXYZL>* cloud2 = new pcl::PointCloud<pcl::PointXYZL>();
    
    Eigen::Affine3f trans;
    pcl::getTransformationFromTwoUnitVectorsAndOrigin(y_dir, z_axis, origin, trans);
    
    vector<int> indices;
    indices.push_back(0);
    pcl::transformPointCloud(*cloud, *cloud2, trans);
    
    cout << cloud2->size() << endl;
    for(int i=0; i<cloud2->size(); i++){
        cout << cloud->at(i).getArray3fMap()[0] << " ";
        cout << cloud->at(i).getArray3fMap()[1] << "  -->  ";
        
        cout << cloud2->at(i).getArray3fMap()[0] << " ";
        cout << cloud2->at(i).getArray3fMap()[1] << endl;
    }
    
    
    delete cloud;
    delete cloud2;
    return 0;
}

