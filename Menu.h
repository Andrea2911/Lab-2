// Lab 1:       War Eagle Chat System
// File:        Menu.h
// Description: Class definition of the Menu class.

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <fstream>
#include "User.h"
#include "WallPage.h"
#include "HomePage.h"

using namespace std;

// Class: Menu
// Description: This class creates a Menu object which represents
//              the menu of options for the  War Eagle Chat System.  This class
//              handles the user's inputs and displays the output requested
//              by the user.
class Menu {
public:
    Menu() : currentUser("superuser") {}

    void displayMenu();
    bool isUser(string username);
    void postMessage();
    void displayWall();
    void displayHome();
    void addFriends();
    void followHash();
    void userLogon();
    void quit();
    void createWelcome(string banner);


private:
    User currentUser;
    string getUsers();
};


#endif //LAB1_MENU_H
