#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <string>

using namespace std;

struct Point3d{
    double x;
    double y;
    double z;
    string label;
};

void tokenize(const string& str, vector<string>& tokens, const string& delimiters);

void readFile(const char* file, pcl::PointCloud<Point3d>* cloud);

void printCloud(pcl::PointCloud<Point3d>* cloud);



int main(int argc, char** argv) {

    // command line parsing
    int c;
    int digit_optind = 0;
    char *iopt = 0, *oopt = 0;
    
    //if (argc != 5){
    //    std::cout << "coordinate file required!" << std::endl;
    //    return 0;
    //}
    
    while ( (c = getopt(argc, argv, "i:o:")) != -1) {
        int this_option_optind = optind ? optind : 1;
        switch (c) {
        case 'i':
            iopt = optarg;
            break;
        case 'o':
            oopt = optarg;
            break;
        case '?':
            break;
        default:
            printf ("?? getopt returned character code 0%o ??\n", c);
        }
    }
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }
    // end command line parsing
    
   
    pcl::PointCloud<Point3d>* cloud = new pcl::PointCloud<Point3d>();
   
    readFile(iopt, cloud);
    
    //printCloud(cloud);
    
    delete cloud;
    
    return 0;
}

void printCloud(pcl::PointCloud<Point3d>* cloud){
    for (int i=0; i<cloud->size(); i++){
        cout << cloud->points[i].x << " " << cloud->points[i].y << " " <<
                cloud->points[i].z << " " << cloud->points[i].label << endl;
    }
}

void readFile(const char* file, pcl::PointCloud<Point3d>* cloud){
	string line;
	ifstream in (file);
	vector<string> tokens;
	if (in.is_open()){
		while ( in.good() ){
	    	getline (in,line);
	    	if (line.empty()){continue;}
	    	tokens.clear();
			tokenize(line, tokens, "\t \n ");
            Point3d p;
            for(int i=0; i<tokens.size();i++){
                p.x = atof(tokens.at(0).c_str());
                p.y = atof(tokens.at(1).c_str());
                p.z = atof(tokens.at(2).c_str());
                p.label = tokens.at(3);
            }
            cloud->push_back(p);
		}
	   in.close();
	}else{
		cout << "Unable to open file" << endl; 
	} 
}

void tokenize(const string& str, vector<string>& tokens, const string& delimiters){
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos){
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}