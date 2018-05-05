//============================================================================
// Name        : radix-sort.cpp
// Author      : Raymond Zhu & Wesley Ng
// Date        : 9/27/15
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <math.h>

int find_min(int A[], int size){
	int min = A[0];
	for(int i=1; i<size; i++) if (A[i] < min) min = A[i];
	if(min > 0) return 0;
	return min;
}

int find_max(int A[], int size){
    int max = A[0];
    for (int i = 1; i < size; i++) if (A[i] > max) max = A[i];
    return max;
}

void C_sort(int A[], int size, int digit){
    int i, B[size], C[10]={};
    for (i = 0; i < size; i++) C[(A[i])/digit%10]++;
    for (i = 1; i < 10; i++) C[i] += C[i-1];
    for (i = size - 1; i >= 0; i--){
        B[C[(A[i])/digit%10]-1] = A[i];
        C[(A[i])/digit%10]--;
    }
    for (i = 0; i < size; i++) A[i] = B[i];
}

void
RadixSort::sort(int A[], int size){ 
	int min = find_min(A, size);
	for(int i=0; i<size; i++) A[i] -= min;
	int max = find_max(A, size);
    for(int digit = 1; max/digit > 0; digit *= 10) C_sort(A, size, digit);
	for(int i=0; i<size; i++) A[i] += min;
}