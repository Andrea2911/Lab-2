// Lab 1:       War Eagle Chat System
// File:        WallPage.cpp
// Description: Class implementation of the WallPage class.

#include "WallPage.h"

// Function:     createWallPage
// Description:  Finds a user's messages and modifies the parameter messages
//               to be used to display the User's WallPage.
void WallPage::createWallPage(string messageString, vector<string>& messages) {
    string singleMessage;
    while (messageString.length() > 0) {
        unsigned long timeStart = messageString.find("{#") + 2;
        if (timeStart != std::string::npos) {
            unsigned long timeEnd = messageString.find("#}");
            string time = messageString.substr(timeStart, timeEnd - timeStart);
            unsigned long messageEnd = messageString.find("{#", timeEnd + 2);
            if (messageEnd == std::string::npos) {
                messageEnd = messageString.length();
            }

            singleMessage = messageString.substr(timeEnd + 2, messageEnd - timeEnd - 2);
            singleMessage = addNewLines(singleMessage);
            messages.push_back(singleMessage);
            messageString = messageString.substr(messageEnd, std::string::npos);
        }
    }
}

string WallPage::addNewLines(string message) {
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

