/**
* Author : Ahmet Isik
* ID: 21702226
* Section : 02
* Assignment : 5
*/
#ifndef FRIENDNET_H
#define FRIENDNET_H
#include <string>

class FriendNet
{
    public:
        FriendNet(const std::string fileName); // constructor
        FriendNet(const FriendNet& aNet); // copy constructor
        ~FriendNet(); // destructor

        void listFriends(const std::string personName, const int hopNo);
        void displayAverageDegrees();
        void displayDiameters();

    protected:

    private:
        int nodeNo;
        int size;

        struct List{
            std::string name;
            int degree;
            int id;
            int* adjVertices;
            bool visited;
            List() {
                visited = false; // initialize all of people as unvisited
            }
        };
        List* adjList; // node array to keep data

        // private helper methods
        void helperListFriends(const int personId, const int hopNo);
        void makeFalseFriends(const int personId, const int hopNo);
        void DFTforDiameter(int startingVertex, int& diameter);
        void DFT(int startingVertex, double& degreeComp);
        void findDiameter(int measure[], int& diameter);
        void shortestPathAlgorithm(int** twoDimArr, int source, int& realDiameter);

};


#endif // FRIENDNET_H
