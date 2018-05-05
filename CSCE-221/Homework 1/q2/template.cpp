#include <iostream>
#include <string>
using namespace std; 

string a;
string b = "aibohphobia";
string c = "civic";
string d = "adinida";
string e = "tattarrattat";
string f = "computer";
string g = "science";

void test(string input, string z){
	for (int i = input.length()-1; i >= 0; i--){
		z = z + input[i];
	}
		
		
	if(z == input) { cout << z << " is a palindrome!" << endl; }
	else if (z != input) { cout << input << " is NOT a palindrome!" << endl; }
		
}

int main()
{
	try{
		
	bool check = false;
	
	test(b, a);
	test(c, a);
	test(d, a);
	test(e, a);
	test(f, a);
	test(g, a);

		
		return 0;
	}
	catch (exception& e){
		cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch(...){
		cerr << "Oops: unknown exception!\n";
		return 2; 
	}
	
}