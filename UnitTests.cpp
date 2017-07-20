// Lab 2:       Distributed War Eagle Chat System
// File:        UnitTests.cpp
// Description: Driver program to test the User, WallPage, HomePage, and Menu objects.
// To run these tests, there must be a timestamp.txt file containing an integer number,
// as well as a Users.txt file with the following contents:
//      Andrea
//      Elizabeth
// You can compile these tests by navigating to the directory with:
//      UnitTests.cpp
//      User.cpp/User.h
//      WallPage.cpp/WallPage.h
//      HomePage.cpp/HomePage.h
//      Menu.cpp/Menu.h
//      timestamp.txt
//      Users.txt
// Type:
//      g++ UnitTests.cpp User.cpp WallPage.cpp HomePage.cpp Menu.cpp -o testing.out
// Then type:
// ./testing.out
// to run the tests.

#include "User.h"
#include "Menu.h"
#include "HomePage.h"
#include "WallPage.h"
#include <iostream>
#include <cassert>
#include <set>
#include <vector>
using namespace std;

//User tests
void testGetUsername(User& testUser);
void testAddFriend(User& testUser1, User& testUser2);
void testIsFriendFalse(User& testUser1);
void testIsFriendTrue(User& testUser1);
void testAddMessage(User& testUser1);
void testFollowsHashtagFalse(User& testUser1);
void testFollowsHashtagTrue(User& testUser1);
void testAddHashtag(User& testUser1);
void testGetHashtags(User& testUser1);

//WallPage tests
void createWallPageTest();

//HomePage tests
void getUserMessagesTest(HomePage& home, User& user);
void getFriendMessagesTest(HomePage& home);
void getHashtagMessagesTest(HomePage& home);

//Menu tests
void userLogonTest(Menu& newMenu);
void isUserFalseTest(Menu& newMenu);
void isUserTrueTest(Menu& newMenu);
void createWelcomeTest(Menu& newMenu);
void getUsersTest(Menu& newMenu);
void displayMenuTest(Menu& newMenu);
void postMessageTest(Menu& newMenu);
void displayWallTest(Menu& newMenu);
void displayHomeTest(Menu& newMenu);
void addFriendsTest(Menu& newMenu);
void followHashTest(Menu& newMenu);
void quitTest(Menu& newMenu);


//Tests all of the methods of a User object using user input and assert statements.
//Due to the nature of the assert macro if a test fails the program will end.
int main() {
    //User class tests
    User user1("Andrea");
    User user2("Elizabeth");
    testGetUsername(user1);
    cout << "getUsername() successfully tested." << endl;
    testAddFriend(user1, user2);
    cout << "addFriend() successfully tested." << endl;
    testIsFriendFalse(user1);
    cout << "isFriend() successfully tested when result is false." << endl;
    testIsFriendTrue(user1);
    cout << "isFriend() successfully tested when result is true" << endl;
    testAddMessage(user1);
    cout << "addMessage() successfully tested." << endl;
    testFollowsHashtagFalse(user1);
    cout << "followsHashtag() successfully tested when result is false." << endl;
    testFollowsHashtagTrue(user1);
    cout << "followsHashtag() successfully tested when result is true." << endl;
    testAddHashtag(user1);
    cout << "addHashtag() successfully tested." << endl;
    testGetHashtags(user1);
    cout << "getHashtags() successfully tested." << endl;
    cout << "All tests for the User class passed." << endl;

    //WallPage class tests
    createWallPageTest();
    cout << "All tests for the WallPage class passed." << endl;

    //HomePage class tests
    HomePage home;
    getUserMessagesTest(home, user1);
    getFriendMessagesTest(home);
    getHashtagMessagesTest(home);
    cout << "All tests for the HomePage class passed." << endl;

    //Menu class tests
    cout << "The tests for the Menu class require user input to work correctly.\n"
         << "Do you wish to continue? (y/n): " << endl;
    char ans;
    cin >> ans;
    if (ans == 'y') {
        Menu menu;
        userLogonTest(menu);
        isUserFalseTest(menu);
        isUserTrueTest(menu);
        createWelcomeTest(menu);
        getUsersTest(menu);
        displayMenuTest(menu);
        postMessageTest(menu);
        displayWallTest(menu);
        displayHomeTest(menu);
        addFriendsTest(menu);
        followHashTest(menu);
        quitTest(menu);
    }
    return 0;
}

//Tests the getUsername() function of the User class by instantiating
//a user object and asserting that a call to getUsername() equals the
//inputted username.
void testGetUsername(User& testUser) {
    assert(testUser.getUsername() == "Andrea");
}

//Tests the addFriend(string newFriend) method of the User class by creating
//two users and adding second user as a friend of the first user and checking
//that the second user was actually added as a friend.
void testAddFriend(User& testUser1, User& testUser2) {
    testUser1.addFriend(testUser2.getUsername());
    assert(testUser1.isFriend(testUser2.getUsername()));
}

//Tests the isFriend(string username) method of the User class when the result
//is expected to be false (when the user in question is not a friend of the
//current user.
void testIsFriendFalse(User& testUser1) {
    assert(!testUser1.isFriend("Laura"));
}

//Tests the isFriend(string username) method of the User class when the result
//is expected to be true (when the user in question is  a friend of the
//current user.
void testIsFriendTrue(User& testUser1) {
    assert(testUser1.isFriend("Elizabeth"));
}

//Tests the addMessage(string message) method of the User class by checking that
//the posted message can be found in the user's file.
void testAddMessage(User& testUser1) {
    string message = "{#1#}This is a random message.";
    testUser1.addMessage(message);
    string messagesFromFile;
    ifstream inStream;
    inStream.open((testUser1.getUsername() + ".txt").c_str());
    getline(inStream, messagesFromFile);
    unsigned long index = messagesFromFile.find(message);
    assert(index != std::string::npos);
}

//Tests the followsHashtag(string hash) method of the User class when the result
//is expected to be false (when the user is not following the given hashtag).
void testFollowsHashtagFalse(User& testUser1) {
    assert(!testUser1.followsHashtag("#faketag"));
}

//Tests the followsHashtag(string hash) method of the User class when the result
//is expected to be true (when the user is following the given hashtag).
void testFollowsHashtagTrue(User& testUser1) {
    testUser1.addHashtag("#newhash");
    assert(testUser1.followsHashtag("#newhash"));
}

//Tests the addHashtag method of the User class by making sure the method adds
//a new hashtag to the hashtag file of a user.
void testAddHashtag(User& testUser1) {
    testUser1.addHashtag("#anotherhash");
    assert(testUser1.followsHashtag("#anotherhash"));
}

//Tests the getHashtags method of the User class by making sure the hashtags added
//are correctly found and returned in a string.
void testGetHashtags(User& testUser1) {
    string hashtags = testUser1.getHashtags();
    unsigned long hash1index = hashtags.find("#newhash");
    unsigned long hash2index = hashtags.find("#anotherhash");
    assert(hash1index != std::string::npos);
    assert(hash2index != std::string::npos);
}


//class WallPage unit tests

//This test checks that the createWallPage method of the WallPage class correctly modifies
//the vector passed as a parameter to contain the messages in the string parameter.
void createWallPageTest() {
    WallPage wallPage;
    cout << "createWallPageTest" << endl;
    vector<string> messages;
    wallPage.createWallPage("{#1#}message", messages);
    cout << messages.at(0) << endl;
    assert(messages.at(0) == "message");
    cout << "createWallPageTest() passed." << endl;
}


//class HomePage unit tests

//This test checks that the getUserMessages method of the HomePage class correctly modifies
//the set passed as a parameter to contain the user's messages in the string parameter.
void getUserMessagesTest(HomePage& home, User& user) {
    HomePage homePage;
    set<string> messages;
    cout << "HomePage::getUserMessages test" << endl;
    string message = "This is a message";
    homePage.getUserMessages("{#1#}This is a message", user, messages);
    set<string>::iterator iter;
    for (iter=messages.begin(); iter != messages.end(); ++iter) {
        string foundMessage = *iter;
        assert(foundMessage.find(message) !=  std::string::npos);
        }
    cout << "HomePage::getUserMessages test passed" << endl;
}

//This test checks that the getUserMessages method of the HomePage class correctly modifies
//the set passed as a parameter to contain the friend's messages in the string parameter.
void getFriendMessagesTest(HomePage& home) {
    HomePage homePage;
    set<string> messages;
    string user = "random";
    cout << "HomePage::getFriendMessages test" << endl;
    string message = "This is a message";
    homePage.getFriendMessages("{#1#}This is a message", user, messages);
    set<string>::iterator iter;
    for (iter=messages.begin(); iter != messages.end(); ++iter) {
        string foundMessage = *iter;
        assert(foundMessage.find(message) !=  std::string::npos);
    }
    cout << "HomePage::getFriendMessages test passed" << endl;

}

//This test checks that the getUserMessages method of the HomePage class correctly modifies
//the set passed as a parameter to contain the hashtag messages in the string parameter.
void getHashtagMessagesTest(HomePage& home) {
    HomePage homePage;
    set<string> messages;
    string user = "random";
    string hashes = " #hash ";
    cout << "HomePage::getHashtagMessages test" << endl;
    string message = "This is a message #hash";
    homePage.getHashtagMessages("{#1#}This is a message #hash", hashes, user, messages);
    set<string>::iterator iter;
    for (iter=messages.begin(); iter != messages.end(); ++iter) {
        string foundMessage = *iter;
        assert(foundMessage.find(message) !=  std::string::npos);
    }
    cout << "HomePage::getHashtagMessages test passed" << endl;
}



//class Menu unit tests

//This test checks that the userLogon method of the Menu class correctly prompts the user for a username.
//This test is verified by the user.
void userLogonTest(Menu& newMenu) {
    cout << "The userLogon function should prompt the user for a username and log the user on\n"
         << "to the chat system.  This test is verified by the user, so if operations are normal\n"
         << "then the test case passes." << endl;
    newMenu.userLogon();
}

//Tests the isUser method of the Menu class when the result is expected to be false
//(when the given username is not a created user)
void isUserFalseTest(Menu& newMenu) {
    assert (!newMenu.isUser("Laura"));
}

//Tests the isUser method of the Menu class when the result is expected to be true
//(when the given username is a created user)
void isUserTrueTest(Menu& newMenu) {
    assert(newMenu.isUser("Andrea"));
}

//Tests the getUsers method of the Menu class by making sure that the string
//returned by the method contains the usernames of the created users, Andrea
//and Elizabeth.
void getUsersTest(Menu& newMenu) {
    string users = newMenu.getUsers();
    unsigned long user1 = users.find("Andrea");
    unsigned long user2 = users.find("Elizabeth");
    assert(user1 != std::string::npos && user2 != std::string::npos);
}

//This test checks that the createWelcome function of the Menu class correctly
//displays a banner enclosed in a box to the console, and is verified by the user.
void createWelcomeTest(Menu& newMenu) {
    cout << "The createWelcome function works correctly if it displays a banner\n"
         << "centered in a box to the console" << endl;
    newMenu.createWelcome("Welcome");
}

//This test checks that the displayMenu function of the Menu class correctly displays
//the menu and takes user input.  This test is verified by the user.
void displayMenuTest(Menu& newMenu) {
    cout << "The displayMenu function should display the menu\n"
         << "and prompt the user for input.  If everything looks correct, simply\n"
         << "select 'q' to display quit message will be displayed an exit message \n"
         << "and move on to the next test." << endl;
    newMenu.displayMenu();
}

//This test checks that the postMessage function of the Menu class prompts the user for a
//message and the user can enter a message without error.  This test is verified by the user.
void postMessageTest(Menu& newMenu) {
    cout << "The postMessage function should prompt the user for a message to post.\n"
         << "This test is verified by the user, so if operations are normal the test passes" << endl;
    newMenu.postMessage();
}

//This test checks that the displayWall function of the Menu class correctly displays the current
//user's wall page.  This test is verified by the user.
void displayWallTest(Menu& newMenu) {
    cout << "The displayWall function should display the current user's wall page.  This test\n"
         << "is verified by the user, so if operations are normal the test passes" << endl;
    newMenu.displayWall();
}

//This test checks that the displayHome function of the Menu class correctly displays the current
//user's home page.  This test is verified by the user.
void displayHomeTest(Menu& newMenu) {
    cout << "The displayHome function should display the current user's home page.  This test\n"
         << "is verified by the user, so if operations are normal the test passes" << endl;
    newMenu.displayHome();
}

//This test checks that the addFriends function of the Menu class correctly prompts the user for a friend
//to add and adds that friend to the current user's friend file.  This test is verified by the user.
void addFriendsTest(Menu& newMenu) {
    cout << "The addFriends function should prompt the user for a friend to add to their friend list.\n"
         << "This test is verified by the user, so if operations are normal the test passes << endl" << endl;
    newMenu.addFriends();
}

//This test checks that the followHash function of the Menu class correctly prompts the user for a hashtag
//to follow and adds that hashtag to the current user's hashtag file.
void followHashTest(Menu& newMenu) {
    cout << "The followHash function should prompt the user for a hashtag to follow.  This test is\n"
         <<  "verified by the user, so if operations are normal the test passes" << endl;
    newMenu.followHash();
}

//This test checks that the quit function of the Menu class displays a thank-you message.
//This test is verified by the user.
void quitTest(Menu& newMenu) {
    cout << "The quit function should display a thank-you message.  This test is verified by the user,\n"
         << "so if operations are normal, the test passes." << endl;
    newMenu.quit();
}

