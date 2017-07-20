// Lab 2:       Distributed War Eagle Chat System
// File:        Menu.cpp
// Description: Implementation of the Menu class.

#include "Menu.h"

using namespace std;

//Function:     displayMenu
//Description:  Displays the menu for the War Eagle Chat system, giving
//              the user 6 different options for how to proceed.
void Menu::displayMenu() {
    string userChoice; //the user's input
    char choiceChar; //the user's input as one character
    // Take user input, if valid input is given perform the requested operation and continue this
    // loop until the user inputs 'q' for quit, at which point the program gracefully ends.
    do {
        cout << "Add friend (f), Post (p), Follow (t), Wall (w), Home (h), Quit (q) " << endl
             << "Enter option: ";
        getline(cin, userChoice);
        cout << endl;
        //If the user doesn't give any input.
        if (userChoice.length() < 1) {
            cout << "No input was given, please choose one of the above options" << endl << endl;
            continue;
        }
        choiceChar = userChoice.at(0);
        switch (choiceChar) {
            case 'p':
                postMessage();
                break;
            case 'w':
                displayWall();
                break;
            case 'h':
                displayHome();
                break;
            case 'f':
                addFriends();
                break;
            case 't':
                followHash();
                break;
            case 'q':
                quit();
                break;
            default:
                cout << "Invalid input! Try again." << endl << endl;
                break;
        }

    }while(choiceChar != 'q');
}

//Function:     userLogon
//Description:  Logs a user into the Distributed War Eagle Chat System.  If the user does not already exist,
//              he is added to the Users.txt file.  The new or returning user is made the current user and
//              welcomed to the chat system.
void Menu::userLogon() {
    string username;
    bool validName = false;
    while (!validName) {
        cout << "Please enter user name: ";
        cin >> username;
        cin.ignore();
        cout << endl;
        if (username.find("{#") != std::string::npos || username.find("#}") != std::string::npos) {
            cout << "Usernames cannot contain '{#' or '#}', please enter a different username" << endl;
            continue;
        }
        validName = true;

    }
    if (!isUser(username)) {
        ofstream outStream;
        outStream.open("Users.txt", ios::app);
        outStream << username + "\n";
        outStream.close();
    }
    currentUser = User(username);
    string banner = "Welcome to Distributed War Eagle Chat System, " + currentUser.getUsername() + "!";
    createWelcome(banner);
}

//Function:     isUser
//Inputs:       string username
//Outputs:      boolean result of whether a name is a user or not
//Description:  Determines whether a given username is a created user of the War Eagle Chat System.
bool Menu::isUser(string username) {
    ifstream inStream;
    string filename = username + ".txt";
    inStream.open(filename.c_str());
    return inStream.good();
}

//Function:     getUsers
//Outputs:      the users of the chat system
//Description:  Searches the Users.txt file for the existing users and returns a string containing
//              the users.
string Menu::getUsers() {
    string users = "";
    ifstream inStream;
    inStream.open("Users.txt");
    while (!inStream.eof()) {
        string user;
        getline(inStream, user);
        users += user + " ";
    }
    inStream.close();
    return users;
}

// Function:    postMessage
//Description:  Allows a user to post a multiline message.  To end the message,
//              the user enters "#$". The message is appended to the user's file
//              in the form "{#timestamp#}message".
void Menu::postMessage() {
    ifstream inStream;
    ofstream outStream;
    inStream.open("timestamp.txt");
    if (inStream.fail()) {
        cout << "Open failed" << endl;
    }
    int timestamp;
    inStream >> timestamp;
    inStream.close();
    outStream.open("timestamp.txt");
    outStream << timestamp + 1; //Write the incremented timestamp back to the timestamp file
    outStream.close();
    bool validMessage = false;
    while (!validMessage) {
        cout << "Enter message:" << endl;
        stringstream ss;
        ss << timestamp;
        string time = ss.str();
        string message = "";
        string line = "";
        while (true) {
            getline(cin, line);
            if ((line.compare("#$") == 0)) {
                message = message.substr(0, message.length() - 2);
                if (message.find("{#") != std::string::npos || message.find("#}") != std::string::npos) {
                    cout << "Messages cannot contain '{#' or '#', please enter a different message." << endl;
                    break;
                }
                message = "{#" + time + "#}" + message; //The timestamp is stored in the message
                currentUser.addMessage(message);
                validMessage = true;
                break;
            }
            message += line + "&&";
        }

    }
    cout << endl;
    createWelcome("New message added");
}

// Function:    displayWall
// Description: Searches the current user's file for all of the user's own posts.
//              Those messages are then printed to the console in reverse
//              chronological order.  After two messages have been printed,
//              the user is asked if they want to see more messages.  If yes,
//              the rest of the user's messages are printed.  If no, no other
//              messages are printed.
void Menu::displayWall() {
    string singleMessage; //a single message from the message file
    std::vector<string> userMessages; //vector of a User's messages
    string banner = currentUser.getUsername() + "'s Wall Page";
    createWelcome(banner);
    string fileMessages; //all of a user's messages
    ifstream inStream;
    string filename = currentUser.getUsername() + ".txt";
    inStream.open(filename.c_str());
    getline(inStream, fileMessages); //get the user's messages
    inStream.close();
    WallPage wall; //instantiates a WallPage for the current user
    wall.createWallPage(fileMessages, userMessages); //creates a wall page for the user

    int numDisplayed = 0; //current number of messages printed
    //iterate backwards over the User's messages to be printed in reverse chronological order.
    for (unsigned long i = userMessages.size() - 1; i != std::string::npos; i--) {
        // When two messages are printed prompt the user for more messages
        if (numDisplayed == 2) {
            cout << "                       More messages? (yes/no): ";
            string answer;
            getline(cin, answer);
            if (answer == "no" || answer == "No" || answer == "NO") {
                break;
            }
        }
        cout << userMessages.at(i) << endl << endl;
        numDisplayed++;
    }
    createWelcome("End of " + currentUser.getUsername() + "'s Wall Page");
}

// Function:    displayHome
// Description: Searches the all message files for all of the user's own posts,
//              the user's friend's posts, and any posts with hashtags the user follows.
//              Those messages are then printed to the console in reverse
//              chronological order.  After two messages have been printed,
//              the user is asked if they want to see more messages.  If yes,
//              the rest of the messages are printed.  If no, no other
//              messages are printed.
void Menu::displayHome() {
    string singleMessage;
    std::set<string> userMessages;
    string banner = currentUser.getUsername() + "'s Home Page";
    createWelcome(banner);
    HomePage home;
    string hashes = currentUser.getHashtags(); //hashtags followed by the current user
    string users = getUsers();
    stringstream s(users);
    string current;
    //iterate over all of the user's message files
    for (; s >> current;) {
        //find the user's messages
        if (current == currentUser.getUsername()) {
            string filename = currentUser.getUsername() + ".txt";
            ifstream inStream(filename.c_str());
            string messages;
            getline(inStream, messages);
            home.getUserMessages(messages, currentUser, userMessages);
            inStream.close();
        }
        //find the user's friend's messages
        else if (currentUser.isFriend(current)) {
            string filename = current + ".txt";
            ifstream inStream(filename.c_str());
            string messages;
            getline(inStream, messages);
            home.getFriendMessages(messages, current, userMessages);
            inStream.close();
        }
        //find the user's hashtag messages
        else {
            string filename = current + ".txt";
            ifstream inStream(filename.c_str());
            string messages;
            getline(inStream, messages);
            home.getHashtagMessages(messages, hashes, current, userMessages);
            inStream.close();
        }
    }

    int numDisplayed = 0; //current number of messages printed
    //iterate backwards of the messages relevant to the User and print them out
    set<string>::reverse_iterator rit;
    for (rit=userMessages.rbegin(); rit != userMessages.rend(); ++rit) {
        if (numDisplayed == 2) {
            cout << "                       More messages? (yes/no): ";
            string answer;
            getline(cin, answer);
            if (answer == "no" || answer == "No" || answer == "NO") {
                break;
            }
        }
        string message = *rit;
        unsigned long timeStart = message.find(" ");
        message = message.substr(timeStart + 1, std::string::npos);
        cout << message << endl << endl;
        numDisplayed++;
    }
    createWelcome("End of " + currentUser.getUsername() + "'s Home Page");
}

//Function:     addFriends
//Description:  Prompts the user for a friend's username.  If the username
//              is valid, a new friend is added to the current user's
//              friends file.  If the username is invalid, the user is continually
//              prompted until a valid username is entered.
void Menu::addFriends() {
    bool validUser = false; //assumed to be given an invalid user until proven otherwise
    string candidateFriend; //The possible friend to be added
    while (!validUser) {
        cout << "Enter friend's name: ";
        cin >> candidateFriend;
        cout << endl;
        cin.ignore();
        //Repeat if the user inputs an invalid User.
        if (!isUser(candidateFriend)) {
            cout << candidateFriend + " is not a valid user." << endl << endl;
            continue;
        }
        else if (currentUser.isFriend(candidateFriend)) {
            cout << candidateFriend + " is already your friend." << endl << endl;
        }

        validUser = true;
    }
    currentUser.addFriend(candidateFriend);
    createWelcome("Added " + candidateFriend + " to Friend's List");
}

//Function:     followHash
//Description:  Prompts the user for a hashtag topic to follow.  If the hashtag
//              did not exist, it is is added to the user's hashtag file.
void Menu::followHash() {
    bool validHash = false; //hashtag is assumed to be invalid until proven otherwise
    string newHash; //potential new hashtag to be followed
    while (!validHash) {
        validHash = true;
        cout << "Enter hashtag topic: ";
        cin >> newHash;
        cin.ignore();
        cout << endl;
        //insures potential hashtag begins with '#'
        if (newHash.at(0) != '#') {
            validHash = false;
            cout << "Hashtag topics must begin with '#'" << endl << endl;
            continue;
        }
        //Checks that hashtag contains only letters
        string hashString = newHash.substr(1, std::string::npos);
        for (int i = 0; i < hashString.size(); i++) {
            char c = hashString[i];
            if (!((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))) {
                validHash = false;
                cout << "Hashtag topics can only contain letters" << endl << endl;
                continue;
            }
        }
    }
    currentUser.addHashtag(newHash);
    cout << endl;
}

//Function:     quit
//Description:  Displays a closing message, and gracefully exits the program.
void Menu::quit() {
    cout << string(10, ' ') << string(59, '=') << endl
         << string(10, ' ') << "|      Thank you for using the War Eagle Chat System      |" << endl
         << string(10, ' ') << string(59, '=') << endl;
}

//Function:     createWelcome
//Inputs:       The banner string, unique for each situation
//Description:  Creates a welcome banner with unique to each task and
//              length of the current user's username.
void Menu::createWelcome(string banner) {
    string sides = string(59, '=');
    unsigned long size = (57 - banner.length()) / 2;
    if ((57 - banner.length()) % 2 != 0) {
        banner = "|" + string(size + 1, ' ') + banner + string(size, ' ') + "|";
    }
    else {
        banner = "|" + string(size, ' ') + banner + string(size, ' ') + "|";
    }
    cout << string(10, ' ') << sides << endl
         << string(10, ' ') << banner << endl
         << string(10, ' ') << sides << endl << endl;
}