#include "FriendNet.h"
#include <iostream>
using namespace std;
int main() {
    FriendNet F("friends.txt");

    F.listFriends("Selim", 2);
    F.listFriends("Funda", 1);
    F.listFriends("Cigdem", -1);
    cout << endl;

    F.listFriends("Ibrahim", 2);
    F.listFriends("Ibrahim", 3);
    cout << endl;
    F.displayAverageDegrees();
    cout << endl;
    F.displayDiameters();
    cout << endl;

 return 0;
}
