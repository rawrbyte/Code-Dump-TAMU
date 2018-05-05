#include <iostream>
#include <fstream>
#include "TemplateDoublyLinkedList.h"
#include "disjointset.h"

int main(int argc, char **argv) {
  try {

    DisjointSet<char> a(5);
	DListNode<char>* s1 = a.MakeSet(1, 'a'); 
    DListNode<char>* s2 = a.MakeSet(2, 'b'); 
    DListNode<char>* s3 = a.MakeSet(3, 'c'); 
    DListNode<char>* s4 = a.MakeSet(4, 'd');
	DListNode<char>* s5 = a.MakeSet(5, 'e');
	
	cout<<"Sets: "<<endl;
	cout<<a<<endl;
    
	cout<<"a.Union(c, d)"<<endl;	
	a.Union(*s3, *s4);
	cout<<"Sets: "<<endl;
	cout<<a<<endl;
	
	cout<<"a.Union(d, e)"<<endl;
	a.Union(*s4, *s5); 
	cout<<"Sets: "<<endl;
	cout<<a<<endl;	
	
	DListNode<char>* setA = a.FindSet(1);
	DListNode<char>* setB = a.FindSet(*s2);
	DListNode<char>* setD = a.FindSet(*s4);
    cout<<"a.find(a): "<< setA->getElem() <<endl;		
	cout<<"a.find(d): "<< setD->getElem() <<endl;
	
    cout<<"a.Union(a, b)"<<endl;
    a.Union(*setA, *setB); 
	cout<<"Sets: "<<endl;
	cout<<a<<endl;
	
	cout<<"a.Union(a, e) "<<endl;
	a.Union(*setA, *s5);
	cout<<"Sets: "<<endl;
	cout<<a<<endl;
    
	cout<<"a.find(a): "<< a.FindSet(1)->getElem() <<endl;	
    cout<<"a.find(e): "<< a.FindSet(5)->getElem() <<endl;	
	cout<<"listSize(a): "<< s1->getListSize() <<endl;
    cout<<"listSize(e): "<< a.FindSet(5)->getListSize() <<endl; 
  }
  catch(exception &e) {
    cerr << e.what() << endl;
    return -1;
  }
}
