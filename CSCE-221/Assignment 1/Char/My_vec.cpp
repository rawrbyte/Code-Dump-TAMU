/*
My_vec.cpp
Raymond Zhu
CPP file for a vector data structure.
*/
	#include "My_vec.h"
	#include <iostream>
	#include <stdexcept>
	
	constexpr int max_cap = 20;
	
	//constructor
	My_vec::My_vec(){
		size = 0; 
		capacity = max_cap;
		ptr = new char[capacity];
	}
	
	//copy constructor
	My_vec::My_vec(const My_vec& vec){
		this->size = vec.size;
		this->capacity = vec.capacity;
		ptr = new char[capacity];
		for (auto i=0; i<size; i++)
			ptr[i]=vec.ptr[i];
	}
	
	//deconstructor
	My_vec::~My_vec(){
		delete[] ptr;
	}
	
	//assignment Operator
	My_vec& My_vec::operator=(const My_vec& vec){
		if (this != &vec){
			delete[] ptr;
			this->size = vec.size;
			this->capacity = vec.capacity;
			ptr = new char[capacity];
			for (auto i=0; i<size; i++)
				ptr[i]=vec.ptr[i];
		}
		return *this;
	}
	
	//get_size() function
	int My_vec::get_size() const{
		return size;
	}

	//get_capacity() function
	int My_vec::get_capacity() const{
		return capacity;
	}
	
	//overloading [] operator
	char& My_vec::operator[](int i) const{
		if(i<0 || i>=size){
			cerr<< "Out of range"<<endl;
		}
		return ptr[i];
	}
	
	//overloading [] operator
	char& My_vec::operator[](int i){
		if(i<0 || i>=size){
			cerr<< "Out of range"<<endl;
		}
		return ptr[i];
	}
	
	//is_empty() function
	bool My_vec::is_empty() const{
		return (size == 0);
	}
	
	//returns elem at r if within range
	char& My_vec::elem_at_rank(int r) const {
		if (r>=0 || r<size) {return ptr[r];}
		else {cerr << "Out of range" << endl; }
	}
	
	//inserts elem at r 
	void My_vec::insert_at_rank(int r, const char& elem){
		if(r<0){ cerr << "Out of range" << endl; }
		if(r<=size){ size++; }
		else{ size = r+1; }
		
		if(size == capacity){ 
			capacity = 2*capacity; 
			char* temp = new char[capacity];
		for (int i=0; i<capacity; i++){ temp[i] = ptr[i]; }
		delete[] ptr;
		ptr = temp;
		
		}
		
		for (int i=size-1; i>r; i--){ ptr[i] = ptr[i-1]; }
		for (int i=size; i<r; i++){ ptr[i] = '0'; }
		ptr[r] = elem;
		
	}
	
	//replaces elem at r
	void My_vec::replace_at_rank(int r, const char& elem){
		if(r<0 || r>size){ cerr << "Out of range" << endl; }
		ptr[r]=elem;
	}
	

	//removes elem at r
	void My_vec::remove_at_rank(int r){
		if(r<0 || r>size){ cerr << "Out of range" << endl; }
		
		for (int i=r; i<size; i++){
			ptr[i] = ptr[i+1];
		}
		
		--size;
	}
	
	//finds the highest index value
	int find_max_index(const My_vec& v,int size){
		if (size == 1){ return 0; }
		int compare = 0, sort = 0;
		while (sort < size){
			if(v[compare] < v[sort]){
				compare = sort;
				
			}
			++sort;
		}
		return compare;
	}
	
	//sorts index from smallest to largest
	void sort_max(My_vec& vec){
		int swap = ' ';
		int size = vec.get_size();
		for (int i=0; i<size; i++){
			for(int y=i+1; y<size; y++){
				if(vec[i]>vec[y]){
					swap = vec[i];
					vec.replace_at_rank(i, vec[y]);
					vec.replace_at_rank(y, swap);
				}
			}
		}
		cout << vec << endl;
	}
	
	//overloading << operator 
	ostream& operator<<(ostream& out, const My_vec& vec){
		out<<"[";
		int size = vec.get_size();
		for(int i = 0; i<size; i++){
			out<< " " << vec[i] << " ";
		}
		out<<"]";
		return out;
	}
	
	