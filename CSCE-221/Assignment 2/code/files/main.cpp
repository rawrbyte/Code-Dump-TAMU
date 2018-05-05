#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

void generateRan(int size);
void generateSort(int size);
void generateRev(int size);
//Generates a random, reversed, and sorted file of integers 
//run with space separated arguments for number of items in file
//example:
// 		compile: g++ -std=c++11 main.cpp
//		./a.out 100 1000 10000
int main(int argc, char *args[])
{
  for (int i = 1; i < argc; i++)
  {
    generateSort(stoi(args[i]));
    generateRev(stoi(args[i]));
    generateRan(stoi(args[i]));
  }
  return 0;
}

void generateSort(int size)
{
  std::ofstream outputFile;
  outputFile.open("seq-sort-" + to_string(size) + ".txt");
  outputFile << size << endl;
  for(int i = 1; i <= size; i++)
  {
    outputFile << i << endl;
  }
  outputFile.close();
}

void generateRev(int size)
{
  std::ofstream outputFile;
  outputFile.open("seq-rev-" + to_string(size) + ".txt");
  outputFile << size << endl;
  for(int i = size; i > 0; i--)
  {
    outputFile << i << endl;
  }
  outputFile.close();
}

void generateRan(int size)
{
  std::ofstream outputFile;
  outputFile.open("seq-ran-" + to_string(size) + ".txt");
  outputFile << size << endl;
  for(int i = 1; i <= size; i++)
  {
    outputFile << rand()%size << endl;
  }
  outputFile.close();
}
