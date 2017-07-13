// Lab 1:       War Eagle Chat System
// File:        UserTests.cpp
// Description: Driver program to test the User object.
// To run these tests, compile the program by navigating to the directory with
// this file and User.cpp/User.h.  Type:
// g++ UserTests.cpp User.cpp -o testing.out
// Then type:
// ./testing.out
// to run the tests.

#include "User.h"
#include <iostream>
#include <cassert>
using namespace std;

//Tests all of the methods of a User object using user input and assert statements.
//Due to the nature of the assert macro if a test fails the program will end.
int main() {
    char ans;
    do {
        string candidateUser;
        cout << "Enter a username for a User object: ";
        cin >> candidateUser;
        cin.ignore();
        User newUser(candidateUser);
        assert(newUser.getUsername() == candidateUser);
        cout << endl << "User " + newUser.getUsername() + " successfully created." << endl;
        string secondUser;
        cout << "Enter a second username for a User object: ";
        cin >> secondUser;
        cin.ignore();
        User anotherUser(secondUser);
        cout << endl << "The first user is not a friend of the second user" << endl;
        assert(!(newUser.isFriend(anotherUser.getUsername())));
        cout << "The second user is added as a friend of the first user" << endl;
        newUser.addFriend(anotherUser.getUsername());
        assert (newUser.isFriend(anotherUser.getUsername()));
        cout << "The second user is now a friend of the first user." << endl;
        string hashtag;
        string hashtagBuffer;
        cout << "Enter a hashtag for the first user to 'follow': ";
        cin >> hashtag;
        cin.ignore();
        hashtagBuffer = hashtag + " " + newUser.getUsername();
        string followedHash = newUser.findFollowedHashtags(hashtagBuffer, newUser.getUsername());
        assert(followedHash.find(hashtag) != std::string::npos);
        cout << "The hashtag " + hashtag + " was successfully followed" << endl;
        cout << "The User object has been successfully tested, do you want to test again? (y/n): ";
        cin >> ans;
        cin.ignore();
        cout << endl;
    } while (ans == 'y' || ans == 'Y');
    return 0;
}