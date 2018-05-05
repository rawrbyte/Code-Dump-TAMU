#include <ostream>

using namespace std;

class My_range{
	
	//member variables
	int pos, count, range, num, hold;
	int *ptr;
	
public:	
	//member functions
	My_range();
	~My_range();
	int get_range() const;
	int get_pos() const;
	int get_count() const;
	int get_num() const;
	void set_range(const int& elem);
	void set_num(const int& elem);
	int get_seed(const int& max, const int& min);
	bool verdict(int p, int r, int ct, char c);
	
};

	My_range::My_range(){
		range = 0; 
		pos = 1;
		count = 0;
		num = 0;
		hold = 0;
		ptr = new int;
	}
	
	My_range::~My_range(){
		delete ptr;
	}

	void My_range::set_range(const int& elem){
		range = elem;
	}
	
	void My_range::set_num(const int& elem){
		num = elem;
	}
	
	int My_range::get_range() const{
		return range;
	}
	
	int My_range::get_pos() const{
		return pos;
	}

	int My_range::get_count() const{
		return count;
	}
	
	int My_range::get_num() const{
		return num;
	}
	
	int My_range::get_seed(const int& max, const int& min){
		num = (max+min)/2;
		++count;
		return num;
	}
	
	bool My_range::verdict(int p, int r, int ct, char c){
		if (c == 'l'){
			if (count == 1){
				pos = p;
				range = r;
				return false;
			}
			else if (pos <= p){
				pos = p+1;
				return false;
			}

		}
	
		else if (c == 'h'){
			if (count == 1){
				
				pos = 1;
				range = p;
				
				return false;
			}
			else if (pos <= p){
				range = p-1;
				return false;
			}

		}
		else if (c == 'y'){
			return true;
		}	
	}

vector<int> vector_range(vector<int> v, int r){
	for(int i=1; i<=r; i++){
		v.push_back(i);
	}
	
	return v;
}

int in_index(vector<int> set, int r){
	int x = 0;
	int index = 0;
	for(int j=0; j<set.size(); j++){
		if(r != set[j]){
			++x;
		}
		if(r == set[j]){
			index = j;
		}
	}
	
	if(x>11){ throw x; }
	return index;
}

void in_range(int r, int num){
	
	if (num <= 0 || num > r){
		throw num;
	}
}

void print_vector(vector<int> v, int r){
	for(int i=0; i<r; i++){
		cout << v[i] << " ";
	}	
}

void attempt(My_range& guess, int pos, int num, int range, char input, bool check){
	while (check == false){
	pos = guess.get_seed(guess.get_range(), guess.get_pos());
		cout << "The computer guessed the value: " << pos << endl;
		if(pos == num){
			cout << "It is equal to your target number: " << num << endl;
		}
	cout << "The number compared to " << num << " is: ";
		cin >> input;
	check = guess.verdict(pos, range, guess.get_count(), input);
	}
	
}