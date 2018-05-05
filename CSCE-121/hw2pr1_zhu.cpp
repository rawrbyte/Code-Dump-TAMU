//Raymond Zhu
//CSCE 121-501
//Due: February 10, 2015 
//hw2pr1_zhu.cpp

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


int main()
{
	try{
	
		int u_input, keeper;
		string esp;
		vector<int> number = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
		vector<string> spanish = {"cero", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve", 
		"diez", "once", "doce", "trece", "catorce", "quince", "dieciseis", "diecisiete", "dieciocho", "diecinueve"};
	
		cout << "Welcome to the number translator!\n";
		cout << "Here the program will translate digital numbers to spanish.\n";

		do
		{
			cout << "Enter a value:" << " ";
			u_input = checker(u_input);
			keeper = u_input;
			if ((u_input >= 0) && (u_input <=19))
			{
				for (int i = 0; i<=19; i++)
				{
					if(u_input == number[i])
					{
						esp = spanish[i];
						cout << esp << ", is " << keeper << " in Spanish." << endl;
					}
				}
			}
			else 
			{
				cout << "Knowledge not that wide with the value: " << keeper << '\n';
			}
		} while ((u_input >= 0) || (u_input <=0));
	
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
	
