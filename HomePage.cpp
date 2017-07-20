// Lab 2:       Distributed War Eagle Chat System
// File:        HomePage.cpp
// Description: Class implementation of the HomePage class.

#include "HomePage.h"

// Function:     getUserMessages
// Inputs:       string of user messages
//               a User object
//               a set that will be filled with user messages
// Description:  Finds a User's messages and modifies the parameter messages
//               to be used to display the User's HomePage.
void HomePage::getUserMessages(string userMessages, User user, set<string> &messages) {
    string singleMessage;
    while (userMessages.length() > 0) {
        unsigned long timeStart = userMessages.find("{#") + 2;
        if (timeStart != std::string::npos) {
            unsigned long timeEnd = userMessages.find("#}");
            string time = userMessages.substr(timeStart, timeEnd - timeStart);
            unsigned long messageEnd = userMessages.find("{#", timeEnd + 2);
            if (messageEnd == std::string::npos) {
                messageEnd = userMessages.length();
            }
            singleMessage = userMessages.substr(timeEnd + 2, messageEnd - timeEnd - 2);
            singleMessage = addNewLines(singleMessage);
            singleMessage = time + " " + user.getUsername() + " >\n" + singleMessage; //add the timestamp and username
            messages.insert(singleMessage);
            userMessages = userMessages.substr(messageEnd, std::string::npos);
        }
    }
}

// Function:     getFriendMessages
// Inputs:       string of user messages
//               a friend's username
//               a set that will be filled with user messages
// Description:  Finds a friend's messages and modifies the parameter messages
//               to be used to display the User's HomePage.
void HomePage::getFriendMessages(string userMessages, string user, set<string> &messages) {
    string singleMessage;
    while (userMessages.length() > 0) {
        unsigned long timeStart = userMessages.find("{#") + 2;
        if (timeStart != std::string::npos) {
            unsigned long timeEnd = userMessages.find("#}");
            string time = userMessages.substr(timeStart, timeEnd - timeStart); //get the timestamp
            unsigned long messageEnd = userMessages.find("{#", timeEnd + 2);
            if (messageEnd == std::string::npos) {
                messageEnd = userMessages.length();
            }
            singleMessage = userMessages.substr(timeEnd + 2, messageEnd - timeEnd - 2);
            singleMessage = addNewLines(singleMessage);
            singleMessage = time + " " + user + " >\n" + singleMessage; //add the timestamp and username

            messages.insert(singleMessage);
            userMessages = userMessages.substr(messageEnd, std::string::npos);
        }

    }

}

// Function:     getHashtagMessages
// Inputs:       string of user messages
//               string of hashtags followed by a user
//               a username
//               a set that will be filled with user messages
// Description:  Finds messages containing a hashtag followed by a user and modifies the parameter messages
//               to be used to display the User's HomePage.
void HomePage::getHashtagMessages(string userMessages, string hashes, string otherUser, set<string> &messages) {
    string singleMessage; //one message
    while (userMessages.length() > 0) {
        unsigned long timeStart = userMessages.find("{#") + 2;
        if (timeStart != std::string::npos) {
            unsigned long timeEnd = userMessages.find("#}");
            string time = userMessages.substr(timeStart, timeEnd - timeStart); //find the time stamp
            unsigned long messageEnd = userMessages.find("{#", timeEnd + 2);
            if (messageEnd == std::string::npos) {
                messageEnd = userMessages.length();
            }
            singleMessage = userMessages.substr(timeEnd + 2, messageEnd - timeEnd - 2);
            singleMessage = addNewLines(singleMessage);
            singleMessage = time + " " + otherUser + " >\n" + singleMessage; //add the timestamp and username

            if (singleMessage.find("#") != std::string::npos) {
                stringstream hashStream(hashes);
                string hashtag;
                for (; hashStream >> hashtag;) {
                    if (singleMessage.find(hashtag) != std::string::npos) {
                        messages.insert(singleMessage); //the messages will be ordered since sets are ordered
                        break;
                    }
                }
            }
            userMessages = userMessages.substr(messageEnd, std::string::npos);
        }

    }

}

//Function:     addNewLines
//Inputs:       a message string
//Outputs:      formatted message string
//Description:  takes a message and replaces all occurrences of "&&" with "\n"
string HomePage::addNewLines(string message) {
    string updatedMessage = "";
    while (message.length() > 0) {
        unsigned long newLine = message.find("&&");
        if (newLine != std::string::npos) {
            updatedMessage += message.substr(0, newLine) + "\n";
            message = message.substr(newLine + 2, std::string::npos);
        }
        else {
            updatedMessage += message;
            message = "";
        }
    }
    return updatedMessage;
}


