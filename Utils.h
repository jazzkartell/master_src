#include <string>
#include <iostream>
#include <vector>
#include <pcl/point_types.h>
#include <fstream>
#include "Point2D.h"
#include <stdlib.h>

using namespace std;


void tokenize(const string& str, vector<string>& tokens, const string& delimiters){
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos){
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void readFile(const char* file, pcl::PointCloud<Point2D>* cloud){
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
                p.set_x(atof(tokens.at(0).c_str()));
                p.set_y(atof(tokens.at(1).c_str()));
                p.set_label(tokens.at(2).c_str());
            }
            cloud->push_back(p);
		}
        in.close();
	}else{
		cout << "Unable to open file" << endl; 
	} 
}