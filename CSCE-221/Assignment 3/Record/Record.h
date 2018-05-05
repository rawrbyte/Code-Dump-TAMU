#include <cstdlib>
#include <iostream>
#include <string>

#ifndef RECORD
#define RECORD
using namespace std;

// list node
class Record {
private:
    string lastName;
    string firstName;
    string uin;
    string phone;
public:
    Record():lastName(""), firstName(""), uin(""),phone("") {}

    Record(string lastName, string firstName, string uin, string phone)
    :lastName(lastName), firstName(firstName), uin(uin),phone(phone) {}
    string getLastname() const { return lastName; }
    string getFirstname() const { return firstName; }
    string getUin() const { return uin; }
    string getPhone() const { return phone; }
    
//    ostream& operator<<(ostream& out, const Record& r);
    bool operator<(const Record& r) const;
};

// output operator
ostream& operator<<(ostream& out, const Record& r){
    out << r.getLastname()<< endl << r.getFirstname()<< endl << r.getUin() << endl << r.getPhone() << endl;
    return out;
}


bool Record::operator<(const Record& r) const {
    if (this->lastName < r.lastName) return true;
    else if(this->lastName == r.lastName){
        if (this->firstName < r.firstName) return true;
        else if(this->firstName == r.firstName){
            if (this->uin <= r.uin) return true;
            else return false;
        }
        else return false;
    }
    else return false;
    
}

#endif