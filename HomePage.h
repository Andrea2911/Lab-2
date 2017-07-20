// Lab 2:       Distributed War Eagle Chat System
// File:        HomePage.h
// Description: Class definition of the HomePage class.

#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include "User.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

class HomePage {
public:
    void getUserMessages(string userMessages, User user, set<string>& messages);
    void getFriendMessages(string userMessages, string user, set<string>& messages);
    void getHashtagMessages(string userMessages, string hashes, string otherUser, set<string>& messages);
private:
    string addNewLines(string message);
};


#endif //HOMEPAGE_H
