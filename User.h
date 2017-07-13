// Lab 1:       War Eagle Chat System
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
//              name, a list of friends, and various operations associated
//              with the user.
class User {
public:
    User(std::string username);


    std::string getUsername();
    void addFriend(std::string newFriend);
    bool isFriend(std::string username);
    bool operator<(const User& right) const;
    std::string findFollowedHashtags(std::string hashBuffer, std::string username);
    void addMessage(std::string message);
    bool followsHashtag(std::string hash);
    void addHashtag(std::string hashtag);
    std::string getHashtags();
private:
    std::string name;
    std::set<std::string> friends;

};


#endif //LAB1_USER_H
