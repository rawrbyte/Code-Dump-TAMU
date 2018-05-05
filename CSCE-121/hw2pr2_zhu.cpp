//Raymond Zhu
//CSCE 121-501
//Due: February 10, 2015 
//hw2pr2_zhu.cpp

#include "std_lib_facilities_4a.h"
using namespace std;

int main()
{
	try{
	
		vector <char> pin = {'7','2','9','1'};
		string guess;
		int bull = 0, cow = 0;
		cout << "Welcome to the game Bulls and Cows!" << endl;
		cout << "Your goal is to get four cows by guessing a four digit number." << endl;
		cout << "None of the four individual values can be the same number." << endl;
	
		do{
	
		cout << "Enter a four digit number: ";
		cin >> guess;

		while (guess.length() != 4){
			cout << "Input length is not four characters!\n" << "Enter a four digit number: ";
			cin >> guess;
		}
		
		for (int x = 0; x<=3; x++) // obtained from http://www.cplusplus.com/reference/cctype/isdigit/
			
			while(!(isdigit(guess[x]))){
				cout << "There was an error in your input!\n" << "Enter a four digit number: ";	
				cin >> guess;
				while (guess.length() != 4){
					cout << "Input length is not four characters!\n" << "Enter a four digit number: ";
					cin >> guess;
					
				}
				
			x = 0;
			
			}

			bull = 0, cow = 0;
			int y = 0;
			for (int g=0; g<=3; g++){
				for (int z=g+1; z<=3; z++){
					if (guess.at(g) == guess.at(z)){
						++y;
					}
				}
			}
				
				if (y>0){
					cout << "Values cannot be the same.\n";
					continue;
				}
	
				for (int i = 0; i<=3; i++){
					for (int n = 0; n<=3; n++){
						if (guess.at(i) == pin[n]){
							++cow;
							if (guess.at(i) == pin[i]){
								--cow;
								++bull;
							}
						}
					}
				}
	
		cout << bull << " bull(s) and " << cow << " cow(s)." << endl;
	
		} while(bull != 4);
	
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