//Raymond Zhu
//CSCE 121-501
//Due: February 25, 2015 
//hw3pr2_zhu.cpp

#include "std_lib_facilities_4a.h"
using namespace std;

int checker (int value){

	
	while(!(cin >> value)) // obtained from http://www.cplusplus.com/forum/beginner/21595/
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}
	
	return value;
}

void print(vector<int> v, string name)
{
	
	cout << name << endl;
	int size = v.size()-1, next = size - 1;
	double result, last, s_last;
	last = v[size]; s_last = v[next];
	result = last / s_last;
	
	for (int b = 0; b < v.size(); b++)
	{
		cout << v[b] << ' ';
	}
	
	cout << endl;
	cout.precision(3);
	cout << "The last value: " << v[size] << " divided by the next-last value: " << v[next] << " is: " << result << endl;
	
}

void fibonacci(int x, int y, vector<int> v, int n)
{

		int z;
		string name = "Fibonacci Sequence";
		v.push_back(x);
		v.push_back(y);
		
		for (int i = 1; i < n-1; i++)
		{
			z = v[i] + v[i-1];
			v.push_back(z);
		}
		
		print(v, name);
	
}

int main()
{
	
	try{
		
		int x, y, n; 
		vector<int> v;
		cout << "Enter two values to start the Fibonacci sequence and the sequence length: " << endl;
		cout << "First value: "; x = checker(x); 
		cout << "Second value: "; y = checker(y); 
		cout << "Sequence length: "; n = checker(n);
		fibonacci(x, y, v, n);
		
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