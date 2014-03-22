#include<cmath>
#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

int getDimensions();

int** constructMatrix(int vertices, string original);

int errorCheck(int n);

void printMatrix(int **matrix, int vertices);

void populateMatrix(int vertices);

int dijkstraAlgorithm(int **matrix, int vertices, int a, int b);

int main(){
    int vertices = getDimensions();
    populateMatrix(vertices);
    return 0;
}

int errorCheck(int vertices){
    int valid = 1;
    if (cin.fail() || vertices<0 || vertices>100){
	cin.clear();
	cin.ignore(1000,'\n');
	cout<<"Sorry! You didn't input an integer between 1 and 100!  Please try again:  ";
    }
    else
	valid = 0;
    return valid;
}

int getDimensions(){
    int vertices;
    int valid;
    cout<<"Please input the number of vertices in your graph:  ";
    while (1){
	cin>>vertices;
	valid = errorCheck(vertices);
	if (valid == 0)
	    break;
    }
    return vertices;
}

int** constructMatrix(int vertices, string original){
    int **matrix = new int*[vertices];
    if (original == "true"){
	for(int i = 0; i<vertices; i++){
	    matrix[i]=new int[vertices];
	}
    }
    else if (original == "false"){
	for (int i = 0; i<vertices; i++){
	    matrix[i] = new int[2];
	}
    }
    else
	cout<<"Something has gone wrong!"<<endl;
    return matrix;
}

void printMatrix(int **matrix, int vertices){
    cout<<"The matrix currently looks like: "<<endl;
    for(int i = 0; i<vertices; i++){
	for(int j = 0; j<vertices; j++){
	    cout<<matrix[i][j]<<" ";
	}
	cout<<endl;
    }
    cout<<"-------------------------------------"<<endl;
}

void populateMatrix(int vertices){
    int **original = constructMatrix(vertices, "true");
    cout<<"Please input, from left to right, the values in your vertex matrix.  Each edge weight should be placed at the intersection of the two vertices it connects. Your matrix should look something like this:\n0 3 2 0\n3 0 1 1\n2 1 0 0\n0 1 0 0\n\nDon't worry about reaching the end of a row--just start the next row:  ";
    int value, valid, a, b;
    for(int i = 0; i<vertices; i++){
	for(int j = 0; j<vertices; j++){
	    cin>>value;
	    //cout<<"I"<<i<<"J"<<j<<endl;
	    //valid = errorCheck(value);
	    //if (valid == 0)
	    //  break;
	    original[i][j] = value;
	}
    }
    printMatrix(original,vertices);
    cout<<"What two points are you trying to find a path between?  Please enter them as integers:  ";
    cin>>a;
    cin>>b;
    dijkstraAlgorithm(original, vertices, a, b);
}

int findLowest(int **resultMatrix, int vertices){
    int beginning = resultMatrix[0][1];
	for(int j = 0; j<vertices; j++){
	    if (beginning>resultMatrix[j][1] && resultMatrix[j][1]!=0 && resultMatrix[j][1]<100)
		beginning = resultMatrix[j][1];
	}
	return beginning;
}

int dijkstraAlgorithm(int **original, int vertices, int a, int b){
    int **resultMatrix = constructMatrix(vertices, "false"); //Build a 2 by vertices matrix which will correlate the vertex and it's "point value" for the path to it from the origin.
    //populate matrix so that origin is 0, and every other vertex is valued at 101.
    for(int k = 0; k<vertices; k++){ 
	resultMatrix[k][0] = k+1;
	resultMatrix[k][1] = 101;
    }
    resultMatrix[a-1][0] = a;
    resultMatrix[a-1][1] = 0;
    printMatrix(resultMatrix, vertices);
	//Now to start implementing the algorithm!  
    for(int j = 0; j<vertices; j++){
	if (original[a-1][j]!=0){
	    cout<<"Original"<<original[a-1][j]<<"  result"<<resultMatrix[j][1]<<endl;
	    resultMatrix[j][1] += original[a-1][j];
	}
    }
    printMatrix(resultMatrix, vertices);
    return 0;
}



