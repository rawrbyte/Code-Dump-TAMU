//Raymond Zhu
//CSCE 121-501
//Due: February 1st 2015
//hw1pr4_zhu.cpp

#include "std_lib_facilities_4.h"
using namespace std;

int main()
{
	unsigned long long num_rice = 1;
	int sq_ct = 1;
	cout << "Square #: " << sq_ct << '\n';
	cout << "Rice Ct: " << num_rice << '\n';

	do
	{
		num_rice = 2 * num_rice;
		sq_ct++;
		cout << "Square #: " << sq_ct << '\n';
		cout << "Rice Ct: " << num_rice << '\n';
	} while (sq_ct < 64);


	return 0;
}
