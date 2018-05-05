#include <iostream>
#include <vector>
#include "My_range.h"
using namespace std;

int main()
{
	try{
	//	vector<int> v;
	
		vector<int> set = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
	//	vector<int> set = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047};
		int range = 0; 
		int num = 0;
		int index = 0;
		int pos = 1;
		
		char input;
		
		bool check = false;
		
		cout << "Input a range of 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, or 2048: ";
	//	cout << "Input a range of 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047: ";
		cin >> range;
	
		index = in_index(set, range);
	
		cout << "Choose a value between the range of 1 - " << set[index] << ": " ;
		cin >> num;
		
		in_range(set[index], num);
		
		My_range guess;
		guess.set_range(range);
		guess.set_num(num);
		cout << "Input values: correct (y), low (l), or high (h)" << endl;
		attempt(guess, pos, num, range, input, check);
		
		cout << "The computer took: " << guess.get_count() << " guesses!" << endl;
		
		return 0;
		}

	catch (exception& e){
		cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (int){
		cerr << "Range Error" << endl;
		return 2;
	}	
	catch(...){
		cerr << "Oops: unknown exception!\n";
		return 3; 
	}
	
}