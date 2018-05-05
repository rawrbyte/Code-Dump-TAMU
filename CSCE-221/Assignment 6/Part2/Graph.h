#pragma once

#include "TemplateDoublyLinkedList.h"
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Edge {
public:
  int vertex_i, vertex_j;
  double weight;
  Edge(int i, int j, double w) {vertex_i=i; vertex_j=j; weight=w;}
};

class Vertex {
public:
  int index;
  Edge* edge = NULL;
  Vertex(int i): index(i) {}
};
  
struct GraphException : public exception {
  GraphException(){}
  GraphException(const string &message){
    msg = "Graph exception:" + message;
  }
  const char* what() const noexcept{
    return msg.c_str();
  }

  string msg;
};

class Graph {
public:
  int n, e;     // |V|, |E|
  int curEdges = 0;
  
  vector<DListNode<Vertex>*> AdjacencyList;
  vector<Edge*> EdgeList;
  vector<Edge*> MST;

public:
  Graph(){}
  void buildGraph();
  void insertEdge(int i, int j, double w);
  double getWeight(int i, int j);
  void sortEdge();     //Sort the weight of edges from small to large
  double MSTAlgo();
  void displayMST(vector<Edge*> List) {
    cout<<"The Minimum Spanning Tree is: "<<endl;
    cout<<"Node  Node  Weight"<<endl;
    for (int i=0; i<(n-1); i++) {
      cout<<setw(3)<<List[i]->vertex_i;
      cout<<setw(6)<<List[i]->vertex_j;
      cout<<setw(7)<<List[i]->weight<<endl;
    }
  }
};

inline istream& operator>>(istream &is, Graph &A) {
  int v;
  double w;
  is >> A.n >> A.e;
  A.buildGraph();
  for (int i=0;i<A.n;i++) {
    v = 0;
    while (v != -1) {
      is >> v;
      if (v != -1) {
        is >> w;
         if (A.getWeight(i,v) == 0) A.insertEdge(i, v, w);
      }
    }
  }  
  return is;
}

inline ostream& operator<<(ostream &os, Graph &A) {
  cout<<"The Adjacency Matrix of the Graph is:"<<endl;
  for (int i=0;i<A.n;i++) {
    for (int j=0;j<A.n;j++)
      cout<<setw(5)<<A.getWeight(i,j);
    cout<<endl;
  }
}


  