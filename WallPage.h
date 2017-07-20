// Lab 2:       Distributed War Eagle Chat System
// File:        WallPage.h
// Description: Class definition of the WallPage class.

#ifndef WALLPAGE_H
#define WALLPAGE_H
#include "User.h"
#include <vector>

using namespace std;

// Class: WallPage
// Description: This class creates a WallPage object which represents
//              a WallPage for a user of the War Eagle Chat System.
//              Allows for a WallPage to be created for a given User.
class WallPage {
public:
    void createWallPage(string messageBuffer, vector<string>& messages);

private:
    string addNewLines(string message);
};


#endif //LAB1_WALLPAGE_H
