//Raymond Zhu
//CSCE 121-501
//Due: February 10, 2015 
//hw2pr4_zhu.cpp

#include "std_lib_facilities_4a.h"

using namespace std;

double JDN_Cal(double year, double month, double day)
{
	double JDN, a, y, m;
	a = ((14-month)/12);
	y = year + 4800 - a;
	m = month + 12*a - 3;
	JDN = day + (((153*m)+2)/5) + 365*y + (y/4) - (y/100) + (y/400) - 32045;

	return JDN;
}

double checker (double value){

	
	while(!(cin >> value)) // obtained from http://www.cplusplus.com/forum/beginner/21595/
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}
	
	return value;
}

int main()
{
	 
	try{
	
		int sub;
		double u_year, u_month, u_day, m_year = 1999, m_month = 8, m_day = 11, synodic = 29.530588853, u_JDN, m_JDN, c_JDN, day_JDN;
		cout.precision(7); // obtained from http://stackoverflow.com/questions/554063/how-do-i-print-a-double-value-with-full-precision-using-cout
		cout << "Enter the date: " << endl;
		cout << "Year: ";
		u_year = checker(u_year);
		cout << "Month: ";
		u_month = checker(u_month);
		cout << "Day: ";
		u_day = checker(u_day);
	
		u_JDN = JDN_Cal(u_year, u_month, u_day);	
		m_JDN = JDN_Cal(m_year, m_month, m_day);
	
		if (u_JDN > m_JDN){
			c_JDN = u_JDN-m_JDN;
		}
		else if (m_JDN > u_JDN){
			c_JDN = abs(m_JDN-u_JDN-synodic);
		}
	
		day_JDN = c_JDN / synodic;
		sub = day_JDN;
		day_JDN = day_JDN - sub;
		day_JDN = day_JDN * synodic;
		cout << "It has been: "  << day_JDN << " day(s) since the last New Moon." << endl;
	
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