//Raymond Zhu
//CSCE 121-501
//Due: February 10, 2015 
//hw2pr3_zhu.cpp

#include "std_lib_facilities_4a.h"
using namespace std;

char int_to_char_conv(int x){

	switch(x){
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		default:
			return '0';
		}
}

vector<char> number_gen(int seed, vector<char> change){

	int y;
	
	do{
	
		int num1, num2, num3, num4;
		char a, b, c, d;
		srand(seed);
		num1 = randint(9);
		num2 = randint(9);
		num3 = randint(9);
		num4 = randint(9);
		a = int_to_char_conv(num1);
		b = int_to_char_conv(num2);
		c = int_to_char_conv(num3);
		d = int_to_char_conv(num4);
		change[0] = a;
		change[1] = b;
		change[2] = c;
		change[3] = d;
	
		y = 0;
			for (int g=0; g<=3; g++){
				for (int z=g+1; z<=3; z++){
					if (change.at(g) == change.at(z)){
						++y;
					}
				}
			}
				
			if (y>0){
				cout << "Number generation error. Not user error.\n" << "Enter a random number: ";
				cin >> seed;
				continue;
			}
		} while (y != 0);

	return change;
	
}

int main()
{
	try{
	
		vector <char> pin = {'7','2','9','1'};
		string guess;
		int bull = 0, cow = 0, seed;
		cout << "Welcome to the game Bulls and Cows!" << endl;
		cout << "Your goal is to get four cows by guessing a four digit number." << endl;
		cout << "None of the four individual values can be the same number." << endl;
	
		do{
		
		if (bull == 4){
			bull = 0;
			cout << "Enter a random number: ";
			cin >> seed;
			pin = number_gen(seed, pin);
			
		}
		
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
	
		} while(bull <= 4);
	
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