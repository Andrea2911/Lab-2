// Lab 2:       Distributed War Eagle Chat System
// File:        User.cpp
// Description: Class implementation of the User class.


#include "User.h"

using namespace std;

// Function:    User constructor
// Description: Assigns the given username to the field name.
User::User(string username) {
    name = username;
    string filename = username + ".txt";
    ofstream outStream;
    outStream.open(filename.c_str(), ios::app);
    outStream.close();
    filename = username + ".Friends.txt";
    outStream.open(filename.c_str(), ios::app);
    outStream.close();
    filename = username + ".Hashtags.txt";
    outStream.open(filename.c_str(), ios::app);
    outStream.close();
}

// Function:    getUsername
// Outputs:     string with the user's name
// Description: Returns the username of a user.
string User::getUsername() {
    return name;
}

// Function:    addFriend
// Inputs:      The name of a friend.
// Description: Adds a new friend to the User's friend file.
void User::addFriend(string newFriend) {
    if (!isFriend(newFriend)) {
        ofstream outStream;
        string filename = getUsername() + ".Friends.txt";
        outStream.open(filename.c_str(), ios::app);
        outStream << newFriend + "\n";
        outStream.close();
    }
}

// Function:    isFriend
// Inputs:      Username of a possible friend
// Outputs:     True if the username is already a friend
// Description: Determines whether a given name is a friend of the User.
bool User::isFriend(string username) {
    ifstream inStream;
    string filename = getUsername() + ".Friends.txt";
    inStream.open(filename.c_str());
    while (!inStream.eof()) {
        string nextFriend;
        getline(inStream, nextFriend);
        if (nextFriend == username) {
            inStream.close();
            return true;
        }
    }
    inStream.close();
    return false;
}

// Function:     getHashtags
// Outputs:      a string containing the hashtags the user follows
// Description:  Searches through the user's hashtags file for all of the
//               hashtags the user follows.
string User::getHashtags() {
    string filename = getUsername() + ".Hashtags.txt";
    ifstream inStream(filename.c_str());
    string friends = "";
    while (!inStream.eof()) {
        string nextFriend;
        getline(inStream, nextFriend);
        friends += nextFriend + " ";
    }
    inStream.close();
    return friends;
}

//Function:     addHashtag
//Inputs:       a new hashtag to be followed
//Description:  Adds a new hashtag topic to a user's hashtag file.
void User::addHashtag(std::string hashtag) {
    if (!followsHashtag(hashtag)) {
        ofstream outStream;
        string filename = getUsername() + ".Hashtags.txt";
        outStream.open(filename.c_str(), ios::app);
        outStream << hashtag + "\n";
        outStream.close();
    }
}

//Function:     followsHashtag
//Inputs:       hashtag string
//Outpus:       true if the user follows the hashtag
//Description:  Looks through the user's hashtag file to determine if the given hashtag string
//              is followed by the user.
bool User::followsHashtag(std::string hash) {
    ifstream inStream;
    string filename = getUsername() + ".Hashtags.txt";
    inStream.open(filename.c_str());
    while (!inStream.eof()) {
        string nextHash;
        getline(inStream, nextHash);
        if (nextHash == hash) {
            inStream.close();
            return true;
        }
    }
    inStream.close();
    return false;
}

//Function:     addMessage
//Inputs:       message string
//Description:  Posts a message to the user's file.
void User::addMessage(std::string message) {
    ofstream outStream;
    string filename = getUsername() + ".txt";
    outStream.open(filename.c_str(), ios::app);
    outStream << message;
    outStream.close();
}
