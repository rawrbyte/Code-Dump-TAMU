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
	bool verdict(int p, int r, int i);
	
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
		num = rand() % (max - min) + min;
		count = 1;
		return num;
	}
	
	bool My_range::verdict(int p, int r, int i){
		count++;
		if (i < p){
				cout << "low" << endl;
				return false;
		}
	
		else if (i > p){
				cout << "high" << endl;
				return false;
		}

		else if (i == p){
			cout << "correct" << endl;
			return true;
		}	
	}

vector<int> vector_range(vector<int> v, int r){
	for(int i=1; i<=r; i++){
		v.push_back(i);	
	}
	
	return v;
}

void in_index(vector<int> set, int i){
	int x = 0;
	int index = 0;
	for(int j=0; j<set.size(); j++){
		if(set[i] != set[j]){
			++x;
		}
	}	
	if(x>12){ throw x; }
	
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

void attempt(My_range& guess, int pos, int num, int range, int input, bool check){
	while (check == false){
		cout << "Pick a value between the range 1 - " << range <<": ";
			cin >> input;
		in_range(range, input);
		
		cout << "You guessed the value: " << input << endl;
		if(input == num){
			cout << "Your guess is equal to the target value" << endl;
			break;
		}
	cout << "The number is: ";
	check = guess.verdict(num, range, input);
	}
	
}