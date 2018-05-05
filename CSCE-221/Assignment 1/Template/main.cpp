
// main.cpp
// Raymond Zhu
//Tests all functionality of the My_vec class.

#include <iostream>
#include <stdexcept>
#include "My_vec.h"


int main(){
try{
	cout << "---------------------- CHAR TEST ----------------------" << endl;
	
																				// define an object v of My_vec type
	My_vec<char> v;
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
	My_vec<char> v1(v);
																					// use the overloaded operator << to display the vector v1
	cout << v1 << endl << endl;
																					cout << "replace a character at the rank 2 of the vector v1 with the character 'Y'" << endl;
	v1.replace_at_rank(2, 'Y');
																					// use the overloaded operator << to display vector v1 elements
	cout << v1 << endl << endl;
																					// define an object v2 of My_vec type
	My_vec<char> v2;
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
	
	cout << "---------------------- INT TEST ----------------------" << endl;
	
																				// define an object v of My_vec type
	My_vec<int> a;
																					cout << "insert 3 at the rank 0 into the vector a" << endl;
	a.insert_at_rank(0, 3);
																					// use the overloaded operator << to display vector elements
	cout << a << endl;
																					// display the vector v size
	cout << " Size of vector: " << a.get_size() << endl << endl;
	
																					cout << "insert 6 at the rank 0 into the vector a" << endl;
	a.insert_at_rank(0, 6);
																					// use the overloaded operator << to display vector elements
	cout << a << endl;
																					// display the vector v size
	cout << " Size of vector: " << a.get_size() << endl << endl;
	
	
	
	
	
																					cout << "insert 7 at the rank 10 into the vector a" << endl;
	a.insert_at_rank(10, 7);
																					// use the overloaded operator << to display vector elements
	cout << a << endl;
																					// display the vector v size
	cout << " Size of vector: " << a.get_size() << endl << endl;
	
																					cout << "remove a integer at the rank 2 from the vector a" << endl;
	a.remove_at_rank(2);
																					// use the overloaded operator << to display vector elements
	cout << a << endl;
																					// display the vector v size
	cout << " Size of vector: " << a.get_size() << endl << endl;
	
																					cout << "replace a character at the rank 2 by the integer 1" << endl; 
	a.replace_at_rank(2, 1);
																					// use the overloaded operator << to display vector elements
	cout << a << endl;
																					// display the vector v size
	cout << " Size of vector: " << a.get_size() << endl << endl;
	
																					cout << "create a copy a1 of the vector a using a copy constructor" << endl;
	My_vec<int> a1(a);
																					// use the overloaded operator << to display the vector v1
	cout << a1 << endl << endl;
																					cout <<  "replace a number at the rank 2 of the vector a1 with the number 5" << endl;
	a1.replace_at_rank(2, 5);
																					// use the overloaded operator << to display vector v1 elements
	cout << a1 << endl << endl;
																					// define an object v2 of My_vec type
	My_vec<int> a2;
																					cout << "insert 2 at the rank 0 into the vector a2" << endl;
	a2.insert_at_rank(0, 2);
																					// use the overloaded operator << to display vector elements
	cout << a2 << endl;
																					// display the vector v2 size
	cout << " Size of vector: " << a2.get_size() << endl << endl;
	
																					cout << "test the assignment operator and copy the vector a1 to a2" << endl; 
	a2 = a1;
																					// use the overloaded operator << to display vector v2
	cout << a2 << endl;
																					// display the vector v2 size
	cout << " Size of vector: " << a2.get_size() << endl << endl;
	
																					cout << "test the function find_max_index using a2" << endl;
																					
	cout << a2[find_max_index(a2, a2.get_size())] << endl << endl;
	
																					cout << "test the function sort_max using a2" << endl;
	sort_max(a2);
																					cout << endl << "replace in the vector a2 a number at the rank 14 with 8" << endl;
	a2.replace_at_rank(14, 8);

	cout << "---------------------- FLOAT TEST ----------------------" << endl;
	
																				// define an object v of My_vec type
	My_vec<float> b;
																					cout << "insert 5.56 at the rank 2 into the vector b" << endl;
	b.insert_at_rank(2, 5.56);
																					// use the overloaded operator << to display vector elements
	cout << b << endl;
																					// display the vector v size
	cout << " Size of vector: " << b.get_size() << endl << endl;
	
																					cout << "insert 6.626 at the rank 4 into the vector b" << endl;
	b.insert_at_rank(4, 6.626);
																					// use the overloaded operator << to display vector elements
	cout << b << endl;
																					// display the vector v size
	cout << " Size of vector: " << b.get_size() << endl << endl;
	
	
	
	
	
																					cout << "insert 1.13 at the rank 12 into the vector b" << endl;
	b.insert_at_rank(12, 1.13);
																					// use the overloaded operator << to display vector elements
	cout << b << endl;
																					// display the vector v size
	cout << " Size of vector: " << b.get_size() << endl << endl;
	
																					cout << "remove a float at the rank 3 from the vector b" << endl;
	b.remove_at_rank(3);
																					// use the overloaded operator << to display vector elements
	cout << b << endl;
																					// display the vector v size
	cout << " Size of vector: " << b.get_size() << endl << endl;
	
																					cout << "replace a float at the rank 2 by the float 11.56" << endl; 
	b.replace_at_rank(2, 11.56);
																					// use the overloaded operator << to display vector elements
	cout << b << endl;
																					// display the vector v size
	cout << " Size of vector: " << b.get_size() << endl << endl;
	
																					cout << "create a copy b1 of the vector b using a copy constructor" << endl;
	My_vec<float> b1(b);
																					// use the overloaded operator << to display the vector v1
	cout << b1 << endl << endl;
																					cout << "replace a float at the rank 5 of the vector b1 with the float 5.22" << endl;
	b1.replace_at_rank(5, 5.22);
																					// use the overloaded operator << to display vector v1 elements
	cout << b1 << endl << endl;
																					// define an object v2 of My_vec type
	My_vec<float> b2;
																					cout << "insert 2.23 at the rank 0 into the vector b2" << endl;
	b2.insert_at_rank(0, 2.23);
																					// use the overloaded operator << to display vector elements
	cout << b2 << endl;
																					// display the vector v2 size
	cout << " Size of vector: " << b2.get_size() << endl << endl;
	
																					cout << "test the assignment operator and copy the vector b1 to b2" << endl; 
	b2 = b1;
																					// use the overloaded operator << to display vector v2
	cout << b2 << endl;
																					// display the vector v2 size
	cout << " Size of vector: " << b2.get_size() << endl << endl;
	
																					cout << "test the function find_max_index using b2" << endl;
																					
	cout << b2[find_max_index(b2, b2.get_size())] << endl << endl;
	
																					cout << "test the function sort_max using b2" << endl;
	sort_max(b2);
																					cout << endl << "replace in the vector b2 a float at the rank 14 with 8.96" << endl;
	b2.replace_at_rank(14, 8.96);
	
	
	
}

catch(exception &error){
	cerr << "Error: " << error.what() << endl;
}
}
