#include <iostream>
#include <vector>
#include <ctime>
#include "My_range.h"
using namespace std;

int main()
{
	try{
	//	vector<int> v;
		srand(time(NULL));
		vector<int> set = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
		
		int range = 0; 
		int num = 0;
		int index = 0;
		int pos = 1;
		
		int input;
		
		bool check = false;
	
	
		My_range guess;
		index = guess.get_seed(12, 1);
		range = set[index];
		in_index(set, index);
		num = guess.get_seed(range, 1);
		in_range(range, pos);
		
		attempt(guess, pos, num, range, input, check);
		cout << "It took you: " << guess.get_count() << " guesses!" << endl;

		
		
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