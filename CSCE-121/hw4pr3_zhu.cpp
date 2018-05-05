//Raymond Zhu
//CSCE 121-501
//Due: February 25, 2015 
//hw4pr3_zhu.cpp

#include "std_lib_facilities_4a.h"
using namespace std;

bool yes(string input)
{
	
	bool returnValue = false;
	if ((input.at(0) == 'y') || (input.at(0) == 'Y'))  {
		returnValue = true;
	}
	
	return returnValue;
}

void answer(int result)
{
	vector<string> output = { "You are thinking of a TABLE", 
											"You are thinking of a SMARtTV", 
											"You are thinking of a FRUIT TRUCK", 
											"You are thinking of a MACBOOK", 
											"You are thinking of a WATER BOTTLE", 
											"You are thinking of a SAMSUNG GALAXY S6", 
											"You are thinking of an APPLE", 
											"You are thinking of an IPHONE" };
	
	cout << output[result] << endl;
}
	
int main()
{	
	try{
		int result;
		string input;
		bool r1, r2, r3;
		enum { question1 = 1, question2 = 2, question3 = 4 };
		cout << "Answer these three questions" << endl;
		cout << "Are you thinking of a electronic device?: "; cin >> input;
		r1 = yes(input); if (r1 == true) result += question1;
		cout << "Are you thinking of something fruit related?: "; cin >> input;
		r2 = yes(input); if (r2 == true) result += question2;
		cout << "Are you thinking of something that fits in your hand?: "; cin >> input;
		r3 = yes(input); if (r3 == true) result += question3;
		answer(result);
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