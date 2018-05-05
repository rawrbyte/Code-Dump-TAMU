
// main.cpp
// Raymond Zhu
// Tests all functionality of the My_vec class.

#include <iostream>
#include <stdexcept>
#include "My_vec.h"


int main(){
try{
	
																				// define an object v of My_vec type
	My_vec v;
																					cout << "insert 'B' at the rank 0 into the vector v" << endl;
	v.insert_at_rank(0, 'B');
																					// use the overloaded operator << to display vector elements
	cout << v << endl;
																					// display the vector v size
	cout << " Size of vector: " << v.get_size() << endl << endl;
	
																					cout <<  "insert 'A' at the rank 0 into the vector v" << endl;
	v.insert_at_rank(0, 'A');
																					// use the overloaded operator << to display vector elements
	cout << v << endl;
																					// display the vector v size
	cout << " Size of vector: " << v.get_size() << endl << endl;
	
	
	
	
	
																					cout << "insert 'D' at the rank 10 into the vector v" << endl;
	v.insert_at_rank(10, 'D');
																					// use the overloaded operator << to display vector elements
	cout << v << endl;
																					// display the vector v size
	cout << " Size of vector: " << v.get_size() << endl << endl;
	
	
																					cout << "remove a character at the rank 2 from the vector v" << endl;
	v.remove_at_rank(2);
																					// use the overloaded operator << to display vector elements
	cout << v << endl;
																					// display the vector v size
	cout << " Size of vector: " << v.get_size() << endl << endl;
	
																					cout << "replace a character at the rank 2 by the character 'E'" << endl; 
	v.replace_at_rank(2, 'E');
																					// use the overloaded operator << to display vector elements
	cout << v << endl;
																					// display the vector v size
	cout << " Size of vector: " << v.get_size() << endl << endl;
	
																					cout << "create a copy v1 of the vector v using a copy constructor" << endl;
	My_vec v1(v);
																					// use the overloaded operator << to display the vector v1
	cout << v1 << endl << endl;
																					cout << "replace a character at the rank 2 of the vector v1 with the character 'Y'" << endl;
	v1.replace_at_rank(2, 'Y');
																					// use the overloaded operator << to display vector v1 elements
	cout << v1 << endl << endl;
																					// define an object v2 of My_vec type
	My_vec v2;
																					cout << "insert 'K' at the rank 0 into the vector v2" << endl;
	v2.insert_at_rank(0, 'K');
																					// use the overloaded operator << to display vector elements
	cout << v2 << endl;
																					// display the vector v2 size
	cout << " Size of vector: " << v2.get_size() << endl << endl;
	
																					cout << "test the assignment operator and copy the vector v1 to v2" << endl; 
	v2 = v1;
																					// use the overloaded operator << to display vector v2
	cout << v2 << endl;
																					// display the vector v2 size
	cout << " Size of vector: " << v2.get_size() << endl << endl;
	
																					cout << "test the function find_max_index using v2" << endl;
																					
	cout << v2[find_max_index(v2, v2.get_size())] << endl << endl;
	
																					cout << "test the function sort_max using v2" << endl;
	sort_max(v2);
																					cout << endl << "replace in the vector v2 a character at the rank 14 with 'S'" << endl;
	v2.replace_at_rank(14, 'S');
	
	
}

catch(exception &error){
	cerr << "Error: " << error.what() << endl;
}
}
