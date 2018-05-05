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

public:
  Graph() {}
  void buildGraph();
  void insertEdge(int i, int j, double w);
  double getWeight(int i, int j);
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


  