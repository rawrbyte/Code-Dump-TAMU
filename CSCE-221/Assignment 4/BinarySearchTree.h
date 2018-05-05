#include "BinaryNode.h"
#include <stdexcept>
#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

class BinarySearchTree {
private:
    int node_num; // total num in the tree
    BinaryNode *root;
    BinaryNode *insert(int x, BinaryNode *t, int& sc);//insert x into tree t
    BinaryNode *findMin(BinaryNode *t);
    BinaryNode *removeMin (BinaryNode *t);
    BinaryNode *remove(int x, BinaryNode *t);

    void resetSearchcost(BinaryNode* t, int i);    
    void inOrderTraversal( BinaryNode *t, int& sc_total);
    void preOrderTraversal( BinaryNode *t, int& sc_total);
    void postOrderTraversal( BinaryNode *t, int& sc_total);
public:
    // constructor
    BinarySearchTree() { root = NULL; node_num=0; }
    bool isEmpty(){return root == NULL;}
    void remove(int x){ root = remove(x, root); } // remove Key = x
    void insert(int x) {
        int sc=0;
        root=insert(x, root, sc);
    }
    int inOrderTraversal(){
        int sc_total = 0;
        inOrderTraversal(root,sc_total);
        cout<<endl;
        return sc_total;
    }
    int preOrderTraversal(){
        int sc_total = 0;
        preOrderTraversal(root,sc_total);
        cout<<endl;
        return sc_total;
    }
    int postOrderTraversal(){
        int sc_total = 0;
        postOrderTraversal(root,sc_total);
        cout<<endl;
        return sc_total;
    }
    int getNodeNum(){return node_num;}
    
    void OutputTreeLevelByLevel();
    void Outputxt(string filename);
};