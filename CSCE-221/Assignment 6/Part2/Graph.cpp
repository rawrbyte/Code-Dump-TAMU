#include "Graph.h"
#include "disjointset.h"
#include "TemplateDoublyLinkedList.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool sortfunction (Edge* i, Edge* j){ 
  return (i->weight < j->weight);
}

void Graph::buildGraph() {
  if((n<0) || (e<0)){
    throw GraphException("either row or column is negative!");
  }
  for(int i = 0; i < n; i++){
	AdjacencyList.push_back(new DListNode<Vertex>(i, Vertex(i)));
  }    
}

void Graph::insertEdge(int i, int j, double w) {
  if(curEdges >= e){
    throw GraphException("edge number is not correct!");
  }
  bool match = false;
  Edge* temp = new Edge(i,j,w);
  
  for(int k = 0; k < EdgeList.size(); ++k){
    if((EdgeList[k]->vertex_i == i && EdgeList[k]->vertex_j == j) || (EdgeList[k]->vertex_i == j && EdgeList[k]->vertex_j == i)){
	  match = true;
	  temp = EdgeList[k];
	}
  }
  EdgeList.push_back(temp);
  
  DListNode<Vertex>* tempi = new DListNode<Vertex>(j, Vertex(i));
  DListNode<Vertex>* tempj = new DListNode<Vertex>(i, Vertex(j));
  
  tempi->getElemt().edge = temp;
  tempj->getElemt().edge = temp;
  
  AdjacencyList[i]->getTrailer()->setNext(tempj);
  AdjacencyList[i]->setTrailer(AdjacencyList[i]->getTrailer()->getNext());
  
  AdjacencyList[j]->getTrailer()->setNext(tempi);
  AdjacencyList[j]->setTrailer(AdjacencyList[j]->getTrailer()->getNext());
  
  if(!match) curEdges++;
  return;
}

double Graph::getWeight(int i, int j) {
  for(int k = 0; k < EdgeList.size(); ++k){
    if((EdgeList[k]->vertex_i == i && EdgeList[k]->vertex_j == j) || (EdgeList[k]->vertex_i == j && EdgeList[k]->vertex_j == i)){
	  return EdgeList[k]->weight;
	}
  }
  return 0;
}

void Graph::sortEdge() {
  sort(EdgeList.begin(), EdgeList.end(), sortfunction);
}

double Graph::MSTAlgo() {
  DisjointSet<Vertex>* A = new DisjointSet<Vertex>(n);
  double totalweight = 0;
  for(int i = 0; i < n; ++i){
	A->MakeSet(i, AdjacencyList[i]->getElem());
  }
  sortEdge();
  for(int i = 0; i < EdgeList.size(); ++i){
	if(A->FindSet(EdgeList[i]->vertex_i)->getKey() != A->FindSet(EdgeList[i]->vertex_j)->getKey()){
	  A->Union(*(A->FindSet(EdgeList[i]->vertex_i)), *(A->FindSet(EdgeList[i]->vertex_j)));
	  totalweight += EdgeList[i]->weight;
	  MST.push_back(EdgeList[i]);
	}
  }
  
  
  return totalweight;
}


  