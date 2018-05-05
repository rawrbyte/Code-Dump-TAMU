#include<cstddef>
// to define NULL


using namespace std;

class BinaryNode {
private:
    friend class BinarySearchTree;
    int Key;
    int SearchCost;
    BinaryNode *left, *right;
public:
    BinaryNode(int key = 0, int sc=0,BinaryNode *lt = NULL,BinaryNode *rt = NULL) ://constructor
    Key(key),SearchCost(sc), left(lt), right(rt){}// functions
    BinaryNode *getLeft() {return left; }
    BinaryNode *getRight() {return right; }
};


