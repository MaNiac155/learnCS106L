#include <iostream>
#include "SimpleGraph.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>

const double Pi = 3.14159265358979323;
const double kRepel=0.008;
const double kAtt=0.008;
using std::cout;	using std::endl;
using std::string;  using std::cin;
void Welcome();

string promptUserForFile(std::ifstream &stream,string prompt="Enter file name: ",string reprompt="Invalid file! Enter again: ");
int stringToInteger(const string& s);
void readGraphFromFile(SimpleGraph & target,std::ifstream &ifs);
void initNodePos(SimpleGraph& sg);

void forceDirectedLayout(SimpleGraph& sg);

//Force is a struct containing the exorted force on one node.
struct Force{
    double dx;
    double dy;
};


// Main method
int main() {
    Welcome();
    std::ifstream ifs;
    string filename;
    filename=promptUserForFile(ifs);

    SimpleGraph sg;
    readGraphFromFile(sg,ifs);

    initNodePos(sg);

    InitGraphVisualizer(sg);
    DrawGraph(sg);// show the initial state firstly.

    time_t startTime=time(NULL);
    time_t runTime;
    cout<<"Initialize Complete!"<<endl;
    cout<<"Expeted Running Time: ";
    cin>>runTime;

    while(true){
        forceDirectedLayout(sg);

        //use a elapsedTime to stop the program.
        double elapsedTime=difftime(time(NULL),startTime);
        if(elapsedTime>=runTime){
            break;
        }
    }
    return 0;
}

// apply the force-directed layout algorithm
void forceDirectedLayout(SimpleGraph& sg){
    int n=sg.nodes.size();
    std::vector<Force> forces;
    for(int i=0;i<n;i++){
        forces.push_back({0,0});
    }

    for(int i=0;i<n;i++){ // repel force between each pair of nodes.
        for(int j=i+1;j<n;j++){
            double& x0=sg.nodes[i].x;
            double& y0=sg.nodes[i].y;
            double& x1=sg.nodes[j].x;
            double& y1=sg.nodes[j].y;

            double forceRepel=kRepel/sqrt(pow((x1-x0),2)+pow((y1-y0),2));
            double theta=atan2(y1-y0, x1-x0);

            forces[i].dx -= forceRepel*cos(theta);
            forces[i].dy -= forceRepel*sin(theta);
            forces[j].dx += forceRepel*cos(theta);
            forces[j].dy += forceRepel*sin(theta);
        }
    }

    int sum=sg.edges.size();
    for(int i=0;i<sum;i++){// attractive force between Edge start node & Edge end node.
        double& x0=sg.nodes[sg.edges[i].start].x;
        double& y0=sg.nodes[sg.edges[i].start].y;
        double& x1=sg.nodes[sg.edges[i].end].x;
        double& y1=sg.nodes[sg.edges[i].end].y;

        double forceAtt=kAtt*(pow((x1-x0),2)+pow((y1-y0),2));
        double theta=atan2(y1-y0, x1-x0);

        forces[sg.edges[i].start].dx += forceAtt*cos(theta);
        forces[sg.edges[i].start].dy += forceAtt*sin(theta);
        forces[sg.edges[i].end].dx -= forceAtt*cos(theta);
        forces[sg.edges[i].end].dy -= forceAtt*sin(theta);
    }

    for(int i=0;i<n;i++){// apply force to each node.
        sg.nodes[i].x+=forces[i].dx;
        sg.nodes[i].y+=forces[i].dy;
    }

    InitGraphVisualizer(sg);
    DrawGraph(sg);
}


void initNodePos(SimpleGraph& sg){
    int n=sg.nodes.size();
    for(int i=0;i<n;i++){
        sg.nodes[i].x=cos(2*i*Pi/n);
        sg.nodes[i].y=sin(2*i*Pi/n);
    }
}


void readGraphFromFile(SimpleGraph & target,std::ifstream &ifs){
    int nodeNum;
    string nodestr;
    getline(ifs,nodestr);// take in the number of the node.
    nodeNum=stringToInteger(nodestr);

    for(int i=0;i<nodeNum;i++){
        target.nodes.push_back({0,0});
    }
    string line;
    while(getline(ifs,line)){// each line inputs the edges.
        std::istringstream iss(line);
        size_t a,b;
        iss>> a >> b;
        target.edges.push_back({a,b});
    }
}


int stringToInteger(const string& s){
    std::istringstream iss(s);
    int a;
    iss>> a;
    return a;
}
// User Input filename
string promptUserForFile(std::ifstream &stream,string prompt,string reprompt){
    cout<<prompt;
    string filename;
    while(true){
        getline(cin,filename);
        stream.open(filename);
        if(!stream.is_open()) cout<<reprompt;
        else{
            return filename;
        }
    }
}




/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}
