#include<cmath>
#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

int getDimensions();

int** constructMatrix(int vertices, string original);

void printMatrix(int **matrix, int vertices, int original);

void populateMatrix(int vertices);

int findLowest(int **resultMatrix, int vertices);

void dijkstraAlgorithm(int **matrix, int vertices, int a, int b);
