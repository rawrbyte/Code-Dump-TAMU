//Raymond Zhu
//CSCE 121-501
//Due: February 1, 2015 
//hw1pr2_zhu.cpp

#include "std_lib_facilities_4.h"
using namespace std;

string translate(string input)
{

	if (input == "one")
	{
		input = "uno";

	}
	else if (input == "two")
	{
		input = "dos";

	}
	else if (input == "three")
	{
		input = "tres";

	}
	else if (input == "four")
	{
		input = "cuatro";

	}
	else if (input == "five")
	{
		input = "cinco";

	}
	else if (input == "six")
	{
		input = "seis";

	}
	else if (input == "seven")
	{
		input = "siete";
	}
	else if (input == "eight")
	{
		input = "ocho";

	}
	else if (input == "nine")
	{
		input = "nueve";

	}
	else if (input == "ten")
	{
		input = "diez";

	}
	else if (input == "eleven")
	{
		input = "once";

	}
	else if (input == "twelve")
	{
		input = "doce";

	}
	else if (input == "thirteen")
	{
		input = "trece";

	}
	else if (input == "fourteen")
	{
		input = "catorce";

	}
	else if (input == "fifteen")
	{
		input = "quince";

	}
	else if (input == "sixteen")
	{
		input = "dieciseis";

	}
	else if (input == "seventeen")
	{
		input = "diecisiete";

	}
	else if (input == "eighteen")
	{
		input = "dieciocho";

	}
	else if (input == "nineteen")
	{
		input = "diecinueve";

	}
	else
	{
		input = "Sorry";
	}

	return input;

}

int main()
{
	string u_input, keeper;
	cout << "Welcome to the number translator!\n";
	cout << "Here the program will translate numbers from english to spanish.\n";
	cout << "Please input the english number which you would like to translate:" << " ";
	cin >> u_input;
	keeper = u_input;
	u_input = translate(u_input);
	if (u_input != "Sorry")
	{
		cout << "The number you want to translate, " << keeper << ", is " << u_input << " in spanish!\n";
	}
	else
	{
		cout << u_input << "! translator knowledge is not that wide!\n";
	}

	return 0;
}

