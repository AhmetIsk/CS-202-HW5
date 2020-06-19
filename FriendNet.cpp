/**
* Author : Ahmet Isik
* ID: 21702226
* Section : 02
* Assignment : 5
*/
#include "FriendNet.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits.h>
#include <stdio.h>
using namespace std;
// constructor
FriendNet::FriendNet( const string fileName ) {
    ifstream inFile;
    // operation to convert string to char
	std::string s = fileName;

	char chartostr[s.size() + 1];
	s.copy(chartostr, s.size() + 1);
	chartostr[s.size()] = '\0';

    // opens the file with fileName
    inFile.open(chartostr);
    if (!inFile) { // if file is not found, gives a warning message and creates and empty friendship network
        cout << "File " << chartostr << " is not found. Therefore an empty friendship network is created." << endl;
        size = 0;
        adjList = new List [size];
    }
    else {

    int in; // for integer values
    string op; // for person names
    if ( inFile >> size ) {
        adjList = new List [size];

    }
    for (int i = 0; i < size; i++) {
        if ( inFile >> in >> op ) {
            adjList[i].name = op;
            adjList[i].id = in;
        }
        if ( inFile >> in ) {
            adjList[i].degree = in;
            adjList[i].adjVertices = new int[in]; // neighbors are stored in an integer array with degree size
            for ( int k = 0; k < adjList[i].degree; k++ ) {
                if ( inFile >> in )
                    adjList[i].adjVertices[k] = in;
            }
        }
    }
    inFile.close();
    }
}
// destructor
FriendNet::~FriendNet() {
    // at first delete neighbor array
    for ( int i = 0; i < size; i++ )
        delete [] adjList[i].adjVertices;
    // then delete node array
    delete [] adjList;
}
// this is a helper method working recursively to find accessible people with given hop no
void FriendNet::helperListFriends(const int personId, const int hopNo) {
    adjList[personId].visited = true; // source is visited
    for (int i = 0; i < adjList[personId].degree; i++) {
        // visit all neighbors at first degree accessible and mark them visited
        if (!adjList[adjList[personId].adjVertices[i]].visited) {
            adjList[adjList[personId].adjVertices[i]].visited = true;
            cout << adjList[adjList[personId].adjVertices[i]].name << " "; // prints out neighbors
        }
        // stopping condition of recursive method
        if ( hopNo > 1) {
            int newHopNo = hopNo - 1;
            helperListFriends(adjList[personId].adjVertices[i], newHopNo);
        }
    }
}
// this is a helper method that assigns all visited person as unvisited to reuse listFriend method
// it does exactly reverse of helperListFriends method
void FriendNet::makeFalseFriends(const int personId, const int hopNo) {
    adjList[personId].visited = false;
    for (int i = 0; i < adjList[personId].degree; i++) {

        if (adjList[adjList[personId].adjVertices[i]].visited) {
            adjList[adjList[personId].adjVertices[i]].visited = false;
        }
        if ( hopNo > 1) {
            int newHopNo = hopNo - 1;
            makeFalseFriends(adjList[personId].adjVertices[i], newHopNo);
        }
    }
}
// lists the neighbors within given hopNo
void FriendNet::listFriends(const string personName, const int hopNo) {
    int personId = -1;
    // finds the id of person by using personName
    for ( int i = 0; i < size; i++ ) {
        if ( adjList[i].name == personName ) {
            personId = i;
        }
    }
    // if personId does not change, namely if the person id with given name is not found, it gives a warning message
    if ( personId == -1 ) {
        cout << personName << " does not exist in the network." << endl;
    }
    // if hopNo is non-positive, prints out as nobody
    else if ( hopNo <= 0) {
        cout << "People accessible from " << adjList[personId].name << " within " << hopNo << " hops: NOBODY" << endl;
    }
    // if the person degree is 0, again prints out as nobody because there is not any neighbor
    else {
        if (adjList[personId].degree == 0) {
            cout << "People accessible from " << adjList[personId].name << " within " << hopNo << " hops: NOBODY" << endl;
        }
        // prints out the neighbors of the person with given name
        else {
            cout << "People accessible from " << adjList[personId].name << " within " << hopNo << " hops: ";
            helperListFriends( personId, hopNo );
            cout << endl;
            makeFalseFriends( personId, hopNo );
        }
    }
}
// this method calculates total number of connected components in a friendship network
// and calculates the average degree of each connected component
void FriendNet::displayAverageDegrees() {
    int num = 0; // number of connected components
    double degreeComp; // average degree
    double degrees[size]; // keeps the average degrees of connected components
    for (int i = 0; i < size; i++) {
        if (!adjList[i].visited) { // if the person is not visited, carry out a deep first traversal and assign all visited people as visited
           DFT(i, degreeComp);     // this algorithm helps to find different connected components
           degrees[num] = degreeComp; // add their average degrees to array
           num++; // increase number of connected components
        }
    }

    for (int i = 0; i < size; i++)
        adjList[i].visited = false; // assign each person as unvisited to reuse method
    cout << "There are " << num << " connected components. The average degrees are: " << endl;
    for (int i = 0; i < num; i++) // print out the average degrees of each connected component
        cout << "For component " << i << ": " << degrees[i] << endl;
}
// this method makes deep first traversal operation to a graph
// takes a starting point and average degree value as parameters
// modified from course material given by teacher and its working mechanism is given at slides
void FriendNet::DFT(int source, double& degreeComp){
    Stack S;
    nodeNo = size;
    double totalDegree = 0; // total degree
    int numOfComp = 0; // number of people in a connected component
    bool *visited = new bool [nodeNo];

    for (int i = 0; i < nodeNo; i++)
        visited[i] = false;
    visited[source] = true;
    S.push(source);
    totalDegree += adjList[source].degree; // adds source person's degree to total degree
    adjList[source].visited = true; // assign source person as visited
    numOfComp++; // increase number of people in a connected component

    while (!S.isEmpty()){
        int current, a;
        S.getTop(current);
        // for each person's neighbor number assign them as visited and push to the stack
        for (a = 0; a < adjList[current].degree; a++){
            int neighbor;
            neighbor = adjList[adjList[current].adjVertices[a]].id; // i th person's id is adjacent
            if (!visited[neighbor]){
                S.push(neighbor); // push to the stack
                totalDegree += adjList[neighbor].degree; // adds current person's degree to total degree
                adjList[neighbor].visited = true; // assign current person as visited
                numOfComp++; // increase number of people in a connected component
                visited[neighbor] = true;
                break;
            }
        }
    // condition for going back if there is not any unvisited vertex at current
        if (a >= adjList[current].degree) {
            S.pop();
        }
    }
    // finds the average degree
    degreeComp = (double)(totalDegree / numOfComp);
    delete [] visited;
}
// this method makes deep first traversal operation to a graph and designed for finding the diameter of a connected component
// to find diameter, it carries out Dijkstra's shortest path algorithm for each person in a connected component and
// takes the longest of the shortest path as diameter
// It takes a starting point source and diameter value as parameters
// modified from course material given by teacher and its working mechanism is given at slides
void FriendNet::DFTforDiameter(int source, int& realDiameter){
    Stack S;
    // pathLengths is a two dimensional array to be able to implement Dijkstra's shortest path algorithm
    // and stores each person's first degree reachable neighbors as 1 and as 0  for others
    int** pathLengths;
    nodeNo = size;
    int diameter; // diameter of a connected component

    bool *visited = new bool [nodeNo];

    for (int i = 0; i < nodeNo; i++)
        visited[i] = false;
    visited[source] = true;
    S.push(source);
    shortestPathAlgorithm(pathLengths, source, diameter); // conduct a shortest path operation for source person
    realDiameter = diameter; // assigns diameter
    adjList[source].visited = true;

    while (!S.isEmpty()){
        int current, a;
        S.getTop(current);
        // for each person's neighbor number assign them as visited and push to the stack
        for (a = 0; a < adjList[current].degree; a++){
            int neighbor;
            neighbor = adjList[adjList[current].adjVertices[a]].id; // i th person's id is adjacent
            if (!visited[neighbor]){
                S.push(neighbor); // push to the stack
                shortestPathAlgorithm(pathLengths, neighbor, diameter); // conduct a shortest path operation for current adjacent person
                if (diameter > realDiameter) // updates the real Diameter of a connected component if it is bigger than previous one
                    realDiameter = diameter;
                adjList[neighbor].visited = true;

                visited[neighbor] = true;
                break;
            }
        }
        // condition for going back if there is not any unvisited vertex at current
        if (a >= adjList[current].degree) {
            S.pop();
        }
    }
    delete [] visited;
}
// this method displays diameter of each component
void FriendNet::displayDiameters() {
    int num = 0; // number of connected components
    int diameter; // diameter
    int diameters[size]; // keeps diameter of each connected component
    for (int i = 0; i < size; i++) {
        if (!adjList[i].visited) {
           DFTforDiameter(i, diameter); // does deep first traversal and finds connected components. then finds diameter of each connected component
           diameters[num] = diameter;
           num++;
        }
    }
    // assigns each person as unvisited to reuse
    for (int i = 0; i < size; i++)
        adjList[i].visited = false;
    // prints out number of connected components and diameters of them
    cout << "There are " << num << " connected components. The diameters are: " << endl;
    for (int i = 0; i < num; i++)
        cout << "For component " << i << ": " << diameters[i] << endl;

}
// this method is a helper method for shortestPathAlgorithm method and finds the longest shortest path
// if it has bigger path than previous diameter, updates it
void FriendNet::findDiameter(int measure[], int& diameter) {
    diameter = 0;
    for(int i = 0; i < size; i++) {
        if (measure[i] < size) {
            if (measure[i] > diameter)
                diameter = measure[i];
        }
    }
}

// This method conducts Dijkstra's single source shortest path algorithm
// it uses source for source point, diameter and twoDimArr for storing degree's between people
// again for creating its algorithm, teacher's course materials are used.
void FriendNet::shortestPathAlgorithm(int** twoDimArr, int source, int& diameter) {
    // this boolean array becomes true if i th object is there in shortest path
    bool shortestTest[size];
    // distance keeps the distances and used to find the shortest path
    int distance[size];
    // minimum distance
    int minimumDistance;

    // initializes twoDimArr as two dim array and fulfills its elements with 0
    twoDimArr = new int*[size];
    for(int i = 0; i < size; i++)
        twoDimArr[i] = new int[size];
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            twoDimArr[i][k] = 0;
        }
        // then puts 1 to the index which is first degree adjacent to the i th node
        for (int k = 0; k < adjList[i].degree; k++) {
            twoDimArr[i][adjList[i].adjVertices[k]] = 1;
        }
    }
    // assigns all distance variables as infinite and boolean as false
    for (int i = 0; i < size; i++) {
        distance[i] = INT_MAX;
        shortestTest[i] = false;
    }

    // then assign the distance of source person to himself as 0
    distance[source] = 0;

    // this loop finds the shortest path for all people in a connected component
    for (int p = 0; p < size; p++) {
        // minimum values for comparing to the smallest and distance is initialized as infinite
        int minDis = INT_MAX;
        int minInx;
        // this loop finds the shortest path in the distance array and its index
        for (int i = 0; i < size; i++) {
            if ((distance[i] <= minDis) && (!shortestTest[i])) {
                minInx = i;
                minDis = distance[i];
            }
        }
        // assign minimumDistance to minimum index
        minimumDistance = minInx;
        // assign the minimumDistance index as true
        shortestTest[minimumDistance] = true;
        // finds shortest path
        for (int i = 0; i < size; i++) {
            // this condition calculates the total distance namely the shortest path
            if ((twoDimArr[minimumDistance][i] + distance[minimumDistance] < distance[i]) ) {
                if ((distance[minimumDistance] != INT_MAX) && twoDimArr[minimumDistance][i] && !shortestTest[i])
                    distance[i] = twoDimArr[minimumDistance][i] + distance[minimumDistance];
            }
        }
    }
    // finds the longest path of all shortest path which is diameter
    findDiameter(distance, diameter);
    // destruct twoDimArr
    for ( int i = 0; i < size; i++ )
        delete [] twoDimArr[i];

    delete [] twoDimArr;
}

