// Lab 2:       Distributed War Eagle Chat System
// Name:        Andrea E. Walker
// Class:       COMP 2710 Section 2
// Date:        July 20, 2017
// E-Mail:      aew0056@auburn.edu
// User-ID:     aew0056
// Filename:    aew0056_1.cpp
//
// Compiling instructions:
// From the terminal, navigate to the directory where the following files are located:
//   aew0056_2.cpp
//   User.cpp/User.h
//   Menu.cpp/Menu.h
//   WallPage.cpp/WallPage.h
//   HomePage.cpp/HomePage.h
//   timestamp.txt
//
// To compile this program, type:
// "g++ aew0056_2.cpp User.cpp Menu.cpp WallPage.cpp HomePage.cpp -o aew0056_2.out"
// and hit enter. Once the program compiles, type "./aew0056_2.out" and the program will
// begin, prompting the user to enter a username.
//
// Description: This program is a simple distributed chat messaging system
//              that allows users to post messages, friend other users,
//              follow hashtags, display a home page, display
//              a wall page, and quit the application.
// To completely restart the program, you must delete all of the .txt files created by the program,
// except the timestamp.txt file.  There must be a timestamp.txt file in the same directory as the other
// files containing an integer timestamp, or the whole system will not work.
#include <iostream>
#include "Menu.h"

using namespace std;

// Function: main
// Description: Instantiates a Menu object, welcomes the user, logs a new/returning user into the system,
// and displays the menu for the Distributed War Eagle Chat System.
int main() {
    Menu menu;
    menu.createWelcome("Distributed War Eagle Chat System!");
    menu.userLogon();
    menu.displayMenu();
    return 0;
}
