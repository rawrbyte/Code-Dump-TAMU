//Raymond Zhu
//CSCE 121-501
//Due: February 10, 2015 
//hw2pr1_zhu.cpp

#include "std_lib_facilities_4a.h"
using namespace std;

int main()
{
	
	try{
		return 0;
	}
	catch (exception& e){
		cerr << "error: " << << '\n';
		return 1;
	}
	catch(...){
		cerr << "Oops: unknown exception!\n";
		return 2; 
	}
	
}