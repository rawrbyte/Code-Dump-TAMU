#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;

// list node
template <typename T>
class DListNode {
	private:
		int key;
		int listSize;
		T obj;
		DListNode *prev, *next, *representative; 
		DListNode *trailer; //just the representative node has this pointer assigned
	public:
		DListNode(int k, T e = T(), DListNode *p = NULL, DListNode *n = NULL)
		: key(k), obj(e), prev(p), next(n) { listSize = 1; }
		T getElem() const { return obj; }
		T& getElemt() { return obj; }
		DListNode<T> * getNext() const { return next; }
		DListNode<T> * getPrev() const { return prev; }
		void setNext(DListNode* n) { this->next = n; }
		void setPrevious(DListNode* p) { this->prev = p; }
		DListNode<T>* insert_before(T d); // insert the int before this node
		// return a pointer to the inserted node
		DListNode<T>* insert_after(T d); // insert the int after this node
		// return a pointer to the inserted node
		void delete_before(); // delete the node before this node
		void delete_after(); // delete the node after this node
		int getKey() { return key; }
		DListNode<T>* getRepresentative() const;
		DListNode<T>* getTrailer() const;
		void setRepresentative(DListNode* rep);
		void setTrailer(DListNode* trail);
		int getListSize();
		void setListSize(int lSize);
};

template <typename T>
DListNode<T>* DListNode<T>::insert_before(T d) {
	DListNode<T>* temp = new DListNode(d);  //temp pointer // 1 OPERATION

	if(prev!= NULL){   //if previous is not null // 2 OPERATION
		temp -> next = this;    //initialize next // 2 OPERATION
		temp -> prev = prev;   //initialize previous // 2 OPERATION
		prev -> next = temp;   // insert in the list  // 2 OPERATION
		prev = temp;          // 1 OPERATION
	}
	else{       //if null than do a simple insert
		temp -> next = this;  // 2 OPERATION
		prev = temp;   // 1 OPERATION
	}

	return temp; // 1 OPERATION
}

template <typename T>
DListNode<T>* DListNode<T>::insert_after(T d) {
	DListNode<T>* temp = new DListNode(d);   // 2 OPERATION
	if(next != NULL){   //if next is not null do this // 2 OPERATION
		temp -> next = next;      //initialize next and previous // 2 OPERATION
		temp -> prev = this;     // 2 OPERATION
		next -> prev = temp;   //make the connection to insert // 2 OPERATION
		next = temp; // 1 OPERATION
	}
	else{ //if null than do a simple insert
		temp -> prev = this;  // 2 OPERATION
		next = temp; // 1 OPERATION
	}

	return temp;  // 1 OPERATION
}

template <typename T>
void DListNode<T>::delete_before() {
	if(prev!= NULL){   //check if something is there  // 2 OPERATION
		DListNode<T>* temp = prev;         // 1 OPERATION
		temp -> prev-> next = temp-> next;    //change the interconnections  // 4 OPERATION
		temp -> next -> prev = temp -> prev; // 4 OPERATION
		delete temp;        //delete the element // 1 OPERATION
	}
	else{
		cout << ">Error: Nothing is there :(" << endl;
	}
}

template <typename T>
void DListNode<T>::delete_after() {
	if(next != NULL){ //check if something is there
		DListNode<T>* temp = next;  // 1 OPERATION
		next -> prev = this; //change the interconnections // 2 OPERATION
		next = next -> next; // 2 OPERATION
		delete temp;  //delete the element // 1 OPERATION
	}
	else{
		cout << ">Error: Nothing is there :(" << endl;
	}
}

template <typename T>
DListNode<T>* DListNode<T>::getRepresentative() const{
	return representative;
}

template <typename T>
DListNode<T>* DListNode<T>::getTrailer() const{
	return trailer;
}

template <typename T>
void DListNode<T>::setRepresentative(DListNode* rep){
	representative = rep;
}

template <typename T>
void DListNode<T>::setTrailer(DListNode* trail){
	trailer = trail;
}

template <typename T>
int DListNode<T>::getListSize(){
	return listSize;
}

template <typename T>
void DListNode<T>::setListSize(int lSize){
	listSize = lSize;
}