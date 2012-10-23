#include <string>
#include <iostream>
#include <vector>
#include <pcl/point_types.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct Point2D{
    PCL_ADD_POINT4D;
    u_int32_t label_id;
    u_int32_t model_id;
};

void tokenize(const string& str, vector<string>& tokens, const string& delimiters){
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos){
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void readFile(const char* file, pcl::PointCloud<Point2D>::Ptr cloud, vector<string>& labels){
	string line;
	ifstream in (file);
	vector<string> tokens;
	if (in.is_open()){
        while ( in.good() ){
	    	getline (in,line);
	    	if (line.empty()){continue;}
	    	tokens.clear();
            tokenize(line, tokens, "\t \n ");
            Point2D p;
            for(int i=0; i<tokens.size();i++){
                p.getArray3fMap()[0] = (atof(tokens.at(0).c_str()));
                p.getArray3fMap()[1] = (atof(tokens.at(1).c_str()));
                p.getArray3fMap()[2] = (atof(tokens.at(2).c_str()));
            }
            p.label_id = cloud->size();
            cloud->push_back(p);
            labels.push_back(tokens.at(3));
		}
        in.close();
	}else{
		cout << "Unable to open file" << endl; 
	} 
}

void printCloud(pcl::PointCloud<Point2D>::Ptr cloud, vector<string>& labels){
    for (int i=0; i<cloud->size(); i++){
      	printf("%f", cloud->at(i).getArray3fMap()[0]);
	cout << " ";
	printf("%f", cloud->at(i).getArray3fMap()[1]);
	cout << " ";
	printf("%f", cloud->at(i).getArray3fMap()[2]);
	cout << " " << labels.at(cloud->at(i).label_id) << endl;
	// cout << cloud->at(i).getArray3fMap()[0] << " "
       //      << cloud->at(i).getArray3fMap()[1] << " "
       //      << cloud->at(i).getArray3fMap()[2] << " "
       //      << labels.at(cloud->at(i).label_id) << endl;
    }
}
