//Raymond Zhu
//CSCE 121-501
//Due: February 25, 2015 
//hw4pr2_zhu.cpp

#include "std_lib_facilities_4a.h"
using namespace std;

void print(double, double, double, vector <double>);

bool checker(double a, double b, double c){
	bool returnValue = false;
	vector <double> dummy = { 0, 0 ,0 }; 
	if (((a == 0) && ((b && c)) != 0)){
		print(a, b, c, dummy);
		returnValue = true;
		return returnValue;
	}
	else if (((a && b) == 0) && (c != 0)){
		cout << "equation is inconsistent" << endl;
		returnValue = true;
		return returnValue;
	}
	else if ((a && b && c) == 0){
		cout << "value of x can be any value" << endl;
		returnValue = true;
		return returnValue;
	}
	else{
		return returnValue = false;
	}
}

vector <double> root (double a, double b, double c, vector<double> storage){
	double d = ((b*b)-4*a*c), x;
	if (d  > 0) {
		x = (-1*b+sqrt(d))/(2*a);
		storage.push_back(x);
		x = (-1*b-sqrt(d))/(2*a);
		storage.push_back(x);
		return storage;
	}
	else if (d == 0){
		x=(-1*b)/(2*a);
		storage.push_back(x);
		storage.push_back(x);
		return storage;
	}
	else if (d < 0){
		cout << "Roots are complex" << endl;
		storage.push_back(0);
		storage.push_back(0);
		storage.push_back(0);
		return storage;
	}
}

void print(double a, double b, double c, vector <double> storage){
	cout.precision(2);
	if (storage.size() == 2){
		if (storage[0] != storage[1]){	
			for (int i = 0; i < 2; i++){
				cout << "x = " << storage[i] << endl;
				cout << "residual = " << fixed << a*pow(storage[i], 2) + b*storage[i] + c << endl;
			}
		}	
		else{
			cout << "double root x = " << storage[0] << endl;
			cout << "residual = " << fixed << a*pow(storage[0], 2) + b*storage[0] + c << endl;
		}
	}
	else if (a == 0){
		int x = (-1*c)/b;
		cout << "x = " << x << endl;
		cout << "residual = " << b*x+c << endl;
	}
	else{}
	
}

int main()
{
	
	try{		
		double a, b, c, x;
		bool find;
		vector <double> storage;
		cout << "Input a, b, and c with respect to ax^2 + bx + c:" << endl;
		cin >> a >> b >> c;
		find = checker(a, b, c);
		if (find == false){
			storage = root(a, b, c, storage);
			if (storage.size() == 2) print(a, b, c, storage);
		}
		return 0;
	}
	catch (exception& e){
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch(...){
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2; 
	}
	
}