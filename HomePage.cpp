// Lab 1:       War Eagle Chat System
// File:        HomePage.cpp
// Description: Class implementation of the HomePage class.

#include "HomePage.h"

// Function:     createHomePage
// Description:  Finds the messages relevant to a user and modifies the parameter messages
//               to be used to display the User's HomePage.
void HomePage::createHomePage(string messageBuffer, string hashes, User user, set<string> &messages) {
    string singleMessage;
    while (messageBuffer.length() > 0) {
        unsigned long userStart = messageBuffer.find("{#") + 2;
        if (userStart != std::string::npos) {
            unsigned long userEnd = messageBuffer.find("#}");
            string username = messageBuffer.substr(userStart, userEnd - userStart);
            unsigned long messageEnd = messageBuffer.find("{#", userEnd + 2);
            if (messageEnd == std::string::npos) {
                messageEnd = messageBuffer.length();
            }
            singleMessage = messageBuffer.substr(userEnd + 2, messageEnd - userEnd - 2);
            singleMessage = username + " >\n" + singleMessage;

            if (username == user.getUsername()) {
                messages.insert(singleMessage);
            } else if (user.isFriend(username)) {
                messages.insert(singleMessage);
            } else if (singleMessage.find("#") != std::string::npos) {
                stringstream hashStream(hashes);
                string hashtag;
                for (; hashStream >> hashtag;) {
                    if (singleMessage.find(hashtag) != std::string::npos) {
                        messages.insert(singleMessage);
                        break;
                    }
                }
            }
            messageBuffer = messageBuffer.substr(messageEnd, std::string::npos);
        }

    }
}
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
            singleMessage = time + " " + user.getUsername() + " >\n" + singleMessage;
            messages.insert(singleMessage);
            userMessages = userMessages.substr(messageEnd, std::string::npos);
        }
    }
}

void HomePage::getFriendMessages(string userMessages, string user, set<string> &messages) {
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
            singleMessage = time + " " + user + " >\n" + singleMessage;

            messages.insert(singleMessage);
            userMessages = userMessages.substr(messageEnd, std::string::npos);
        }

    }

}

void HomePage::getHashtagMessages(string userMessages, string otherUser, User user, set<string> &messages) {
    string singleMessage;
    string hashes = user.getHashtags();
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
            singleMessage = time + " " + otherUser + " >\n" + singleMessage;

            if (singleMessage.find("#") != std::string::npos) {
                stringstream hashStream(hashes);
                string hashtag;
                for (; hashStream >> hashtag;) {
                    if (singleMessage.find(hashtag) != std::string::npos) {
                        messages.insert(singleMessage);
                        break;
                    }
                }
            }
            userMessages = userMessages.substr(messageEnd, std::string::npos);
        }

    }

}

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


