#include "BinarySearchTree.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void read_file(string filename,BinarySearchTree& bst){
    ifstream ist(filename);
    if (ist.is_open()){
        vector<int> input;
        int number;
        int cnt = 0;
        cout << "Input data:\n";
        while(ist>>number){
            cnt++;
            input.push_back(number);
            cout << number << endl;
        }
        cout << "Create a binary search tree:"<<endl;
        for (int i=0; i<input.size(); i++) {
            bst.insert(input[i]);
        }
        cout << "Total number of nodes is " << cnt << endl;
    }
    else{
        cerr << "Cannot open '"<< filename <<"'."<<endl;
    }
    
}



int main(){
// This part is using for basic example test.

    BinarySearchTree bst;
    cout << "Please input a filename: ";
    string filename;
    cin >> filename;
    read_file(filename,bst);

    cout << "In Order Traversal:" << endl;
    int sc_total = bst.inOrderTraversal();
    cout << "Pre Order Traversal:" << endl;
    bst.preOrderTraversal();
    cout << "Post Order Traversal:" << endl;
    bst.postOrderTraversal();
    cout<< "Average search cost is " << (double) sc_total/(double) bst.getNodeNum() <<'\n';
    if (bst.getNodeNum()>16) {
        cout << "Node number great than 16, please check output file."<<endl;
    }
    else{
        bst.Outputxt("example_o");
        bst.OutputTreeLevelByLevel();
    }

    cout << "Please enter a key to remove: ";
    int num;
    cin >> num;
    bst.remove(num);
    
    if (bst.getNodeNum()>16) {
        cout << "Node number great than 16, please check output file."<<endl;
    }
    else{
        bst.Outputxt("example_o");
        bst.OutputTreeLevelByLevel();
    }
    sc_total = bst.inOrderTraversal();
    cout<< "Average search cost is " << (double) sc_total/(double) bst.getNodeNum() <<'\n';
    cout << "Total number of nodes is " << bst.getNodeNum() << endl;

// This part is for 221-A4-test-files
/*
    ofstream ofs("AverageSC");
    ofs << "Average SC\n";
    char buf[3] = {'p','r','l'};
    for (int i=0; i<3; i++) {
        for (int j=1; j<13; j++) {
            BinarySearchTree bst;
            string path = "./test/";
            path = path + to_string(j) + buf[i];
            read_file(path,bst);
            int sc_total = bst.inOrderTraversal();
            ofs << to_string(j) + buf[i] << "\t" <<(double) sc_total/(double) bst.getNodeNum() <<endl;
        }
    }
    for (int i=0; i<3; i++) {
        for (int j=1; j<5; j++) {
            BinarySearchTree bst;
            string path = "./test/";
            path = path + to_string(j) + buf[i];
            read_file(path,bst);
            bst.Outputxt(to_string(j) + buf[i]);
        }
    }
*/
}