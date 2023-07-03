#include<iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

void printStateBits(istringstream& stream);
int stringToInteger(const string& s);
void stringToIntegerTest();
int getInteger();
string promptUserForFile(ifstream &stream,string prompt="Enter file name: ",string reprompt="error! Enter again: ");

int main(){
    // ostringstream oss("Ito-En Green Tea",stringstream::ate);
    // cout<<oss.str()<<endl;
    // oss<<"16.9 ml";
    // cout<<oss.str()<<endl;
    // istringstream iss("10 minuit");
    // int num;
    // string unit;
    // iss>>num;
    // iss>>unit;


    // return 0;
    //stringToIntegerTest();
    ifstream ifs;
    promptUserForFile(ifs);
    
}

int stringToInteger(const string& s){
    istringstream iss(s);
    int a;
    printStateBits(iss);
    iss>> a;
    printStateBits(iss);
    return a;
}
void stringToIntegerTest(){
    string str;
    while (1)
    {
        cin>>str;
        int res=stringToInteger(str);
        cout<<"You typed in: "<<str<<endl;
        cout<<"the integer is: "<<res<<endl;
        cout<<"the integer /2 is:"<<res/2<<endl;
    }
    

}
void printStateBits(istringstream& stream){
    cout << (stream.good() ? "G" : "-");
    cout << (stream.fail() ? "F" : "-");
    cout << (stream.eof() ? "E" : "-");
    cout << (stream.bad() ? "B" : "-") << endl;
}

int getInteger(){
    string line;
    int val;
    char trash;
    while(true){
        if(!getline(cin,line)) throw domain_error("getInteger error");
        istringstream iss(line);
        if((iss>>val)&&!(iss>>trash)) return val;
    }
}
string promptUserForFile(ifstream &stream,string prompt,string reprompt){
    cout<<prompt;
    string filename;
    while(true){
        getline(cin,filename);
        stream.open(filename);
        if(!stream.is_open()) cout<<reprompt<<endl;
        else{
            return filename;
        }
    }
}