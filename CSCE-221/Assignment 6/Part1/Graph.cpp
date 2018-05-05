#include "Graph.h"
#include "TemplateDoublyLinkedList.h"
#include <iostream>

using namespace std;

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
}

double Graph::getWeight(int i, int j) {
  for(int k = 0; k < EdgeList.size(); ++k){
    if((EdgeList[k]->vertex_i == i && EdgeList[k]->vertex_j == j) || (EdgeList[k]->vertex_i == j && EdgeList[k]->vertex_j == i)){
	  return EdgeList[k]->weight;
	}
  }
  return 0;
}


  