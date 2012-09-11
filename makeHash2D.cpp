//#include "Utils.h"
#include "Point2D.h"
#include <string>
#include <iostream>
#include <pcl/point_types.h>
#include "Utils.h"

using namespace std;

int main(int argc, char** argv) {
    
    pcl::PointCloud<Point2D>* cloud = new pcl::PointCloud<Point2D>();
    
    // we require one file containing the coordinate file as input
    if(argc != 2){
        cout << "Input File required!" << endl;
    }else{
        readFile(argv[1], cloud);
    }
    
    cout << cloud->size() << endl;
    
    delete cloud;
    return 0;
}

