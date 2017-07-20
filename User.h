// Lab 2:       Distributed War Eagle Chat System
// File:        User.h
// Description: Class definition of the User class.


#ifndef USER_H
#define USER_H

#include <set>
#include <string>
#include <sstream>
#include <fstream>

// Class: User
// Description: This class creates a User object which represents
//              a user of the War Eagle Chat System.  Each user has a
//              name, and various operations associated
//              with the user.
class User {
public:
    User(std::string username);
    User() {};

    std::string getUsername();
    void addFriend(std::string newFriend);
    bool isFriend(std::string username);
    void addMessage(std::string message);
    bool followsHashtag(std::string hash);
    void addHashtag(std::string hashtag);
    std::string getHashtags();
private:
    std::string name;
};


#endif //LAB1_USER_H
