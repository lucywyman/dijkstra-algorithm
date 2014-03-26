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

int main(){
    int vertices = getDimensions();
    populateMatrix(vertices);
    return 0;
}

/*********************************
 ** Function description: Get the dimensions of the graph's matrix from 
 the user, and check whether it's valid.  If not, ask the user again. 
 Return the input if it's valid to be used to construct graph's 2D array (matrix). 
 *******************************/
int getDimensions(){
    int vertices, valid = 1;
    cout<<"Please input the number of vertices in your graph:  ";
    while (valid == 1){
	cin>>vertices;
	if (cin.fail() || vertices<0 || vertices>100){
	    cin.clear();
	    cin.ignore(1000,'\n');
	    cout<<"Sorry! You didn't input an integer between 1 and 100! Please try again:  ";
	    valid = 1;
	}
	else
	    valid = 0;
    }
    return vertices;
}

/********************************
 **Function description: Create 2D arrays to represent either the 
 original matrix representing the user's graph, or the 'result matrix' 
 which will keep track of the total paths between two given points. 
 **Parameters: Number of vertices so that we know how big the graph matrix 
 should be, and a variable 'original' to determine whether the
 result matrix or graph matrix is being built.
 **Return: 2D array (matrix) of appropriate size.
 *********************************/
int** constructMatrix(int vertices, int original){
    int **matrix = new int*[vertices];
    if (original == 1){
	for(int i = 0; i<vertices; i++){
	    matrix[i]=new int[vertices];
	}
    }
    else if (original == 0){
	for (int i = 0; i<vertices; i++){
	    matrix[i] = new int[2];
	}
    }
    else
	cout<<"Something has gone wrong!"<<endl;
    return matrix;
}

/********************************
 **Function description: Print a matrix to the screen--similar to above
 this will either be the result matrix or graph matrix.
 *******************************/
void printMatrix(int **matrix, int vertices, int original){
    if (original == 1){
	cout<<"The matrix currently looks like: "<<endl;
	cout<<"    ";
	for (int k = 0; k<vertices; k++)
	    cout<<k+1<<" ";
	cout<<endl<<"    ";
	for (int k = 0; k<vertices; k++)
	    cout<<"- ";
	cout<<endl;
	for(int i = 0; i<vertices; i++){
	    cout<<i+1<<" | ";
	    for(int j = 0; j<vertices; j++){
		cout<<matrix[i][j]<<" ";
	    }
	    cout<<endl;
	}
    }
    else if (original == 0){
	cout<<"Result Matrix"<<endl;
	for(int i = 0; i<vertices; i++){
	    for(int j = 0; j<2; j++){
		cout<<matrix[i][j]<<" ";
	    }
	    cout<<endl;
	}
    }
    cout<<"-------------------------------------"<<endl;
}

/********************************
 **Function description:  Have user input values of the graph matrix, and 
 check whether each value is valid.  If not, have the user re-enter them.
 Also have them input the two points which they want to find the shortest 
 path between.
 *******************************/
void populateMatrix(int vertices){
    int **original = constructMatrix(vertices, 1);
    cout<<"Please input, from left to right, the values in your vertex matrix.  Each edge weight should be placed at the intersection of the two vertices it connects. Your matrix should look something like this:\n0 3 2 0\n3 0 1 1\n2 1 0 0\n0 1 0 0\n\nDon't worry about reaching the end of a row--just start the next row:  ";
    int value, valid, a, b, temp;
    for(int i = 0; i<vertices; i++){
	for(int j = 0; j<vertices; j++){
	    valid = 1; //reset valid
	    while (valid == 1){ //check to make sure input is pos. int.
		cin>>value;
		if (cin.fail() || vertices<0 || vertices>100){
		    cin.clear();
		    cin.ignore(1000,'\n');
		    cout<<"Sorry! You didn't input an integer between 1 and 100!  Please try again:  ";
		    valid = 1;
		}  
		else{
		    original[i][j] = value; //if it's not, go through the loop again.
		    valid = 0;
		}
	    }
	}
    }
    printMatrix(original,vertices, 1); //print to check matrix.
    cout<<"What two points are you trying to find a path between?  Please enter them as integers:  ";
    cin>>a; //should probably check these too.  
    cin>>b;
    if (a>b){
	temp = a;
	a = b;
	b = temp;
    }
    dijkstraAlgorithm(original, vertices, a, b);
}

/****************************************
 **Function description: Find the vertex with the lowest total, in order to make it the new 'point a' in the dijkstra algorithm.  Iterate through the second column of the result matrix and check whether each is lower than the last.
 **************************************/
int findLowest(int **resultMatrix, int vertices){
    int lowestNode = 0;
    int beginning = resultMatrix[0][1];
    for(int j = 0; j<vertices; j++){
	if ((beginning>resultMatrix[j][1] && resultMatrix[j][1]>0 && resultMatrix[j][1]<100) || (beginning == 0)){ 
	    beginning = resultMatrix[j][1];
	    lowestNode = j;
	}
    }
    return lowestNode;
}

/**************************************
 **Function description: Implement the algorithm!
 *************************************/
void dijkstraAlgorithm(int **original, int vertices, int a, int b){
    int originalA = a;
    int **resultMatrix = constructMatrix(vertices, 0); 
    for(int k = 0; k<vertices; k++){ 
	resultMatrix[k][0] = k+1;
	resultMatrix[k][1] = 101;
    }
    resultMatrix[a-1][0] = a;
    resultMatrix[a-1][1] = 0;
    printMatrix(resultMatrix, vertices, 0);
    //now start the algorithm!
    while (a!=b){  
	for(int j = 0; j<vertices; j++){
	    if (original[a-1][j]!=0){ //if there's an edge between verticeswhere a is the starting point and j is the second point
		if (resultMatrix[j][1] == 101) //reset "high" to 0.
		    resultMatrix[j][1] = 0;
		int newTotal = resultMatrix[a][1]+original[a-1][j]; //add edge weight to 'total' associated with vertex.
		if (newTotal<resultMatrix[j][1] || resultMatrix[j][1]==0)
		    resultMatrix[j][1] = newTotal;
	    }
	}
	int newA = findLowest(resultMatrix, vertices);
	cout<<"NEWA "<<newA<<endl;
	a = resultMatrix[newA][0]+1;
	cout<<"result"<<resultMatrix[newA][0]<<endl;
	printMatrix(resultMatrix, vertices, 0);
    }
    cout<<"The shortest path between "<<originalA<<" and "<<b<<" is "<<resultMatrix[b-1][1]<<endl;
}



