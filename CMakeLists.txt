cmake_minimum_required(VERSION 3.7)
project(Lab1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES "UserTests.cpp" "User.cpp" "Menu.cpp" "WallPage.cpp" HomePage.cpp HomePage.h)
add_executable(Lab2 ${SOURCE_FILES})