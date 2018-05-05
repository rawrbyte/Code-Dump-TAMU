#include <iostream>
#include <fstream>
#include "Graph.h"
#include <sys/time.h>

int main(int argc, char **argv) {
  try {
    // read a test matrix file
    Graph A;
    ifstream fin(argv[1]);
    fin >> A;
    fin.close();

    cout<<A;
	cout<<"The total value of the Minimum Spanning Tree is: "<<A.MSTAlgo()<<endl;
    A.displayMST(A.MST);
}
  catch(exception &e) {
    cerr << e.what() << endl;
    return -1;
  }
}
