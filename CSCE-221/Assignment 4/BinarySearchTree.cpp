#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>

//insert an element into the tree
BinaryNode *BinarySearchTree::insert(int x,BinaryNode *t, int& sc){
    sc++;
    if(t == NULL){
        t = new BinaryNode(x);
        t-> SearchCost = sc;
        node_num++;
        cout<<"Key = " << x <<"  SearchCost = "<<sc<<endl;
    }
    else if(x < t->Key)
        t->left = insert(x, t->left, sc);
    else if(x > t->Key)
        t->right = insert(x, t->right, sc);
    else
        cerr << "insert Error: Duplicate item." << endl;
    return t;
}

//find min node in the tree
BinaryNode *BinarySearchTree::findMin(BinaryNode *t){
    if(t == NULL)   cerr << "findMin Error: Empty Tree." << endl;
    while(t->left != NULL) t = t->left;
    return t;
}

//remove min node from the tree
BinaryNode *BinarySearchTree::removeMin(BinaryNode *t){
    if(t == NULL)
        cerr << "removeMin Error: Item Not Found." << endl;
    if(t->left != NULL)
        t->left = removeMin(t->left);
    else {
        BinaryNode *node = t;
        t = t->right;
        delete node;
    }
    return t;
}

//remove a node from the tree
BinaryNode *BinarySearchTree::remove(int x, BinaryNode *t){
    if(t == NULL){
        cerr << "remove Error: Item Not Found." << endl;
        return t;
    }
    if(x < t->Key)
        t->left = remove(x, t->left);
    else if(x > t->Key)
        t->right = remove(x, t->right);
    else if(t->left != NULL && t->right != NULL){
        // item x is found; t has two children
        t->Key = findMin(t->right)->Key;
        t->right = removeMin(t->right);
        node_num--;
        resetSearchcost(root,1);
    }
    else { //t has only one child
        node_num--;
        BinaryNode *node = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete node;
        resetSearchcost(root,1);
    }
    return t;
}


// SearchCost = 1 + depth of the node
void BinarySearchTree::resetSearchcost(BinaryNode* t, int i){
    if(t == NULL) return;
    resetSearchcost(t->left, i+1);
    resetSearchcost(t->right, i+1);
    t->SearchCost=i; //  reset
}

// do a in_order traversal and printout the element
void BinarySearchTree::inOrderTraversal( BinaryNode *t, int& sc_total){
    if(t==NULL)
        cerr << "inOrderTraversal Error: Empty Tree." << endl;
    
    if(t->left != NULL)
        inOrderTraversal(t->left,sc_total);
    if (node_num <17) {
        cout << t->Key <<"["<<t->SearchCost << "] ";
    }
    sc_total += t->SearchCost;
    if(t->right !=NULL)
        inOrderTraversal(t->right,sc_total);
}


// do a pre_order traversal and printout the element
void BinarySearchTree::preOrderTraversal( BinaryNode *t, int& sc_total){
    if(t==NULL)
        cerr << "inOrderTraversal Error: Empty Tree." << endl;
    
    if (node_num <17) {
        cout << t->Key <<"["<<t->SearchCost << "] ";
    }
    sc_total += t->SearchCost;
    if(t->left != NULL)
        preOrderTraversal(t->left,sc_total);
    if(t->right !=NULL)
        preOrderTraversal(t->right,sc_total);
}

// do a post_order traversal and printout the element
void BinarySearchTree::postOrderTraversal( BinaryNode *t, int& sc_total){
    if(t==NULL)
        cerr << "inOrderTraversal Error: Empty Tree." << endl;
    
    if(t->left != NULL)
        postOrderTraversal(t->left,sc_total);
    if(t->right !=NULL)
        postOrderTraversal(t->right,sc_total);
    if (node_num <17) {
        cout << t->Key <<"["<<t->SearchCost << "] ";
    }
    sc_total += t->SearchCost;
}

// output the whole tree level by level
void BinarySearchTree::OutputTreeLevelByLevel() {
    if (!root) return ;
    queue<BinaryNode*> nodesQueue;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;
    nodesQueue.push(root);
    BinaryNode* Xnode=new BinaryNode(-1);
    bool flag = true;
    vector<int> line;
    while (!nodesQueue.empty()) {
        BinaryNode *currNode = nodesQueue.front();
        nodesQueue.pop();
        nodesInCurrentLevel--;
        if (currNode) {
            line.push_back(currNode->Key);
            if (currNode->left==NULL) nodesQueue.push(Xnode);
            else{
                flag = false;
                nodesQueue.push(currNode->left);
            }
            if (currNode->right==NULL) nodesQueue.push(Xnode);
            else{
                flag = false;
                nodesQueue.push(currNode->right);
            }
            nodesInNextLevel += 2;
        }
        if (nodesInCurrentLevel == 0) {
            
            for (int i=0; i<line.size(); i++) {
                if (line[i] == -1)
                    cout <<"X ";
                else
                    cout << line[i]<<" ";
            }
            cout << endl;
            if (flag) {
                return ;
            }
            line.clear();
            flag = true; //initial flag to true
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
}

//save the whole tree to a file
void BinarySearchTree::Outputxt(string filename){
    ofstream ofs(filename.c_str());
    if (!root) return ;
    queue<BinaryNode*> nodesQueue;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;
    nodesQueue.push(root);
    BinaryNode* Xnode=new BinaryNode(-1);
    bool flag = true;
    vector<int> line;
    while (!nodesQueue.empty()) {
        BinaryNode *currNode = nodesQueue.front();
        nodesQueue.pop();
        nodesInCurrentLevel--;
        if (currNode) {
            line.push_back(currNode->Key);
            if (currNode->left==NULL) nodesQueue.push(Xnode);
            else{
                flag = false;
                nodesQueue.push(currNode->left);
            }
            if (currNode->right==NULL) nodesQueue.push(Xnode);
            else{
                flag = false;
                nodesQueue.push(currNode->right);
            }
            nodesInNextLevel += 2;
        }
        if (nodesInCurrentLevel == 0) {
            for (int i=0; i<line.size(); i++) {
                if (line[i] == -1)
                    ofs <<"X ";
                else
                    ofs << line[i]<<" ";
            }
            ofs << endl;
            if (flag) {
                return ;
            }
            line.clear();
            flag = true; //initial flag to true
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
}
