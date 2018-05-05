all: Main

Main: BinarySearchTree.o Main.o
	g++ -std=c++11 BinarySearchTree.o Main.o -o Main

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h BinaryNode.h
	g++ -std=c++11 -c BinarySearchTree.cpp

Main.o: Main.cpp BinarySearchTree.h
	g++ -std=c++11 -c Main.cpp

clean:
	rm *.o Main
