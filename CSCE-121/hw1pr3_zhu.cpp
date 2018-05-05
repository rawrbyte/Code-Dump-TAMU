//Raymond Zhu
//CSCE 121-501
//Due: February 1st 2015
//hw1pr3_zhu.cpp

#include "std_lib_facilities_4.h"
using namespace std;

int main()
{
	int num_rice = 1, sq_ct = 1;
	cout << "Square #: " << sq_ct << '\n';
	cout << "Rice Ct: " << num_rice << '\n';

	do
	{
		num_rice = 2 * num_rice;
		sq_ct++;
		cout << "Square #: " << sq_ct << '\n';
		cout << "Rice Ct: " << num_rice << '\n';	
	} while (num_rice <= 1000);

	cout << '\n';
	cout << "At least: " << sq_ct << " squares for the inventor to obtain 1,000 grains of rice.\n";
	cout << '\n';

	do
	{
		num_rice = 2 * num_rice;
		sq_ct++;
		cout << "Square #: " << sq_ct << '\n';
		cout << "Rice Ct: " << num_rice << '\n';
	} while (num_rice <= 1000000);

	cout << '\n';
	cout << "At least: " << sq_ct << " squares for the inventor to obtain 1,000,000 grains of rice.\n";
	cout << '\n';

	do
	{
		num_rice = 2 * num_rice;
		sq_ct++;
		cout << "Square #: " << sq_ct << '\n';
		cout << "Rice Ct: " << num_rice << '\n';
	} while (num_rice <= 1000000000);

	cout << '\n';
	cout << "At least: " << sq_ct << " squares for the inventor to obtain 1,000,000,000 grains of rice.\n";
	cout << '\n';

	return 0;
}
