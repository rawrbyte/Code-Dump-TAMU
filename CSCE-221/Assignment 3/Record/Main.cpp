#include "TemplateDoublyLinkedList.h"
#include "Record.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>

using namespace std;
// read records from "filename" and save the records in vector phoneBook
void read(vector<DoublyLinkedList<Record> >& phoneBook){
    ifstream filein("PhoneBook.txt");
    string lastName , firstName, uin, phone;
    string tmp_lastName, tmp_firstName, tmp_uin;
    
    if (filein.is_open()){
        while ( !filein.eof()&&(filein >> lastName) && (filein >> firstName) && (filein >> uin) && (filein >> phone)){
            Record newRecord(lastName, firstName, uin, phone);
            phoneBook[(int) lastName.at(0)-(int) 'A'].insertOrderly(newRecord);
        }
    }
    else cout<<"Cannot open PhoneBook.txt."<<endl;
    filein.close();
}

// search for type input
void search(vector<DoublyLinkedList<Record> >& phoneBook, vector<Record>& r, string input, string type){
    vector<Record> output;
    if (type == "lastName") { // search for lastname
        int index=(int)input.at(0)-(int) 'A';
        if (index<0 || index > 25)  return;
        DListNode<Record>* tmp= phoneBook[index].getFirst();
        while(tmp!= phoneBook[index].getAfterLast()){
            if(tmp->getElem().getLastname()==input){
                r.push_back(tmp->getElem());
            }
            tmp = tmp-> getNext();
        }
        return;
    }
    else if(type == "firstName"){// search for firstname
        for (int i=0; i<r.size(); i++) {
            if (r[i].getFirstname()==input)
                output.push_back(r[i]);
        }
        r.clear();
        r.resize(0);
        r = output;
        return;
    }
    else if(type == "uin"){// search for uin
        output.clear();
        output.resize(0);
        for (int i=0; i<r.size(); i++) {
            if (r[i].getUin()==input){
                output.push_back(r[i]);
            }
        }
        r.clear();
        r.resize(0);
        r.push_back(output[0]);
        return;
    }
    else return;
}

// print out the menu
void menu(vector<DoublyLinkedList<Record> >& phoneBook){
    vector<Record> result;
    cout << "Please enter the last name :";
    string input;
    cin >> input;
    search(phoneBook,result,input,"lastName");
    if (result.size() > 1) {
        cout << "More than one record was found!"<<endl;
        cout << "Please enter the first name :";
        cin >> input;
        search(phoneBook,result,input,"firstName");
        if (result.size() > 1) {
            cout << "More than one record was found!"<<endl;
            cout << "Please enter the UIN :";
            cin >> input;
            search(phoneBook,result,input,"uin");
            if (result.size() >= 1) {
                cout << result[0]<<endl;
            }
            else    cout << "No record!"<<endl;
        }
        else if(result.size() == 1)  cout << result[0];
        else    cout << "No record!"<<endl;
    }
    else if(result.size() == 1)   cout << result[0];
    else    cout << "No record!"<<endl;
}
// a function dump the whole phone book to screen
void show(vector<DoublyLinkedList<Record> >& phoneBook){
    for (int i=0; i<26; i++)
        cout<<phoneBook[i];
}

int main () {
    vector<DoublyLinkedList<Record> > phoneBook(26);
    read(phoneBook);
    show(phoneBook);
    menu(phoneBook);
    return 0;
}