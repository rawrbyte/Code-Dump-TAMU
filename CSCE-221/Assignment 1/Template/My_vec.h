/*
My_vec.h
Raymond Zhu
Header file for a vector data template structure.
*/

#include <ostream>

using namespace std;

template <class T>
class My_vec {
	
	//member variables
	int size, capacity;
	T *ptr;
	
public:	
	//member functions
	My_vec();
	~My_vec();
	My_vec(const My_vec<T>& vec);
	My_vec& operator=(const My_vec<T>& vec);
	int get_size() const;
	int get_capacity() const;
	T& operator[](int i) const;
	T& operator[](int i);
	bool is_empty() const;
	T& elem_at_rank(int r) const;
	void insert_at_rank(int r, const T& elem);
	void replace_at_rank(int r, const T& elem);
	void remove_at_rank(int r);
	
};
	template <class T>
	ostream& operator<<(ostream& out, const My_vec<T>& vec);
	
	template <class T>
	int find_max_index(const My_vec<T>& v,int size);
	
	template <class T>
	void sort_max(My_vec<T>& vec);

	constexpr int max_cap = 20;
	
	//constructor
	template <class T>
	My_vec<T>::My_vec(){
		size = 0; 
		capacity = max_cap;
		ptr = new T[capacity];
	}
	
	//copy constructor
	template <class T>
	My_vec<T>::My_vec(const My_vec<T>& vec){
		this->size = vec.size;
		this->capacity = vec.capacity;
		ptr = new T[capacity];
		for (auto i=0; i<size; i++)
			ptr[i]=vec.ptr[i];
	}
	
	//deconstructor
	template <class T>
	My_vec<T>::~My_vec(){
		delete[] ptr;
	}
	
	//assignment Operator
	template <class T>
	My_vec<T>& My_vec<T>::operator=(const My_vec<T>& vec){
		if (this != &vec){
			delete[] ptr;
			this->size = vec.size;
			this->capacity = vec.capacity;
			ptr = new T[capacity];
			for (auto i=0; i<size; i++)
				ptr[i]=vec.ptr[i];
		}
		return *this;
	}
	
	//get_size() function
	template <class T>
	int My_vec<T>::get_size() const{
		return size;
	}

	//get_capacity() function
	template <class T>
	int My_vec<T>::get_capacity() const{
		return capacity;
	}
	
	//overloading [] operator
	template <class T>
	T& My_vec<T>::operator[](int i) const{
		if(i<0 || i>=size){
			cerr<< "Out of range"<<endl;
		}
		return ptr[i];
	}
	
	//overloading [] operator
	template <class T>
	T& My_vec<T>::operator[](int i){
		if(i<0 || i>=size){
			cerr<< "Out of range"<<endl;
		}
		return ptr[i];
	}
	
	//is_empty() function
	template <class T>
	bool My_vec<T>::is_empty() const{
		return (size == 0);
	}
	
	//returns elem at r if within range
	template <class T>
	T& My_vec<T>::elem_at_rank(int r) const {
		if (r>=0 || r<size) {return ptr[r];}
		else {cerr << "Out of range" << endl; }
	}
	
	//inserts elem at r 
	template <class T>
	void My_vec<T>::insert_at_rank(int r, const T& elem){
		if(r<0){ cerr << "Out of range" << endl; }
		if(r<=size){ size++; }
		else{ size = r+1; }
		
		if(size == capacity){ 
			capacity = 2*capacity; 
			T* temp = new T[capacity];
		for (int i=0; i<capacity; i++){ temp[i] = ptr[i]; }
		delete[] ptr;
		ptr = temp;
		
		}
		
		for (int i=size-1; i>r; i--){ ptr[i] = ptr[i-1]; }
		for (int i=size; i<r; i++){ ptr[i] = '0'; }
		ptr[r] = elem;
		
	}
	
	//replaces elem at r
	template <class T>
	void My_vec<T>::replace_at_rank(int r, const T& elem){
		if(r<0 || r>size){ cerr << "Out of range" << endl; }
		ptr[r]=elem;
	}
	
	//removes elem at r
	template <class T>
	void My_vec<T>::remove_at_rank(int r){
		if(r<0 || r>size){ cerr << "Out of range" << endl; }
		
		for (int i=r; i<size; i++){
			ptr[i] = ptr[i+1];
		}
		
		--size;
	}
	
	//finds the highest index value
	template <class T>
	int find_max_index(const My_vec<T>& v,int size){
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
	template <class T>
	void sort_max(My_vec<T>& vec){
		T swap = ' ';
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
	template <class T>	
	ostream& operator<<(ostream& out, const My_vec<T>& vec){
		out<<"[";
		int size = vec.get_size();
		for(int i = 0; i<size; i++){
			out<< " " << vec[i] << " ";
		}
		out<<"]";
		return out;
	}
	
	

		
		
		
		
