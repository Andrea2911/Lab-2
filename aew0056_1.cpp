// Lab 1:       War Eagle Chat System
// Name:        Andrea E. Walker
// Class:       COMP 2710 Section 2
// Date:        June 29, 2017
// E-Mail:      aew0056@auburn.edu
// User-ID:     aew0056
// Filename:    aew0056_1.cpp
//
// Compiling instructions:
// From the terminal, navigate to the directory where the following files are located:
//   aew0056_1.cpp
//   User.cpp/User.h
//   Menu.cpp/Menu.h
//   WallPage.cpp/WallPage.h
//   HomePage.cpp/HomePage.h
//
// To compile this program, type:
// "g++ aew0056_1.cpp User.cpp Menu.cpp WallPage.cpp HomePage.cpp -o aew0056_1.out"
// and hit enter. Once the program compiles, type "./aew0056_1.out" and the program will
// begin, prompting the user to choose an option.
//
// Description: This program is a simple chat messaging system
//              that allows users to post messages, friend other users,
//              follow hashtags, change users, display a home page, display
//              a wall page, and quit the application.
#include <iostream>
#include "Menu.h"

using namespace std;

// Function: main
// Description: Instantiates a Menu object, and uses it to display the user menu for
// the War Eagle Chat System.
int main() {
    Menu menu;
    menu.createWelcome("Distributed War Eagle Chat System!");
    menu.userLogon();
    menu.displayMenu();
    return 0;
}
