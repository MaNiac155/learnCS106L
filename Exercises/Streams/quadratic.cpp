#include <string>
#include <iostream>
#include <cmath> //gives us pow and sqrt!

using std::string; using std::cout;
using std::cin; using std::pow;
using std::sqrt; using std::endl;

//want: a function named quadratic that will take in 3 doubles and return
//a combination of: does a solution exist, and if so, what is it?
	//get radical, test if negative, return indicating no roots
	// radical = b^2 - 4ac
	
	//otherwise get roots and return
	// root1 = (-b + sqrt(radical)) divided by 2a
	// root2 = (-b - sqrt(radical)) divided by 2a
std::pair<bool, std::pair<double,double> > quadratic(double a, double b, double c){
	bool hasRoot;
	double r1;
	double r2;
	double radical=pow(b,2)-4*a*c;
	if(radical<0){
		hasRoot=false;
		r1=0;r2=0;
		}
	else{
		hasRoot=true;
		r1=(-b+sqrt(radical))/(2*a);
		r2=(-b-sqrt(radical))/(2*a);	
	}
	return std::make_pair(hasRoot, std::make_pair(r1,r2));

}

int main() {
	//get 3 doubles (ax^2 + bx + c)
	double a, b, c;
	cout << "Give me 3 coefficients: " << endl;
	
	//This line gets 3 numbers from user input and stores them in a, b and c 
	//we will learn more about cin on Thursday
	cin >> a >> b >> c;

	//some call to quadratic function!
	//get roots if they exist
	//print accordingly

		
	//std::pair<bool, std::pair<double,double> > ans=quadratic(a,b,c);
	auto ans =quadratic(a,b,c);
	bool exists=ans.first;
	auto roots=ans.second;
	if(exists==true){
		cout<<"have a root!"<<endl;
		cout<<"root1: "<<roots.first<<endl;
		cout<<"root2: "<<roots.second<<endl;
	}
	else{
		cout<<"don't have a root"<<endl;
	}
	return 0;
}


//better initialization
int main2(){
	double a, b, c;
	cin >> a >> b >> c;
	auto [found ,result] =quadratic(a,b,c); // Structured binding 
	if(found){
		auto [r1,r2]=result;
		cout<<r1<<endl;
		cout<<r2<<endl;
	}
	else{
		cout<<"no";
	}
	return 0;
}


// Test: x^2 + 5x + 6 = 0, roots = -3, -2

// To run: first compile code --> make quadratic, 
// then run the compiled code --> ./quadratic