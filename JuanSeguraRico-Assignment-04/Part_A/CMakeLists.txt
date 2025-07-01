cmake_minimum_required(VERSION 3.25)
project(Assignment_04_Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_04_Code
        BagInterface.h
        Include.h
        LinkedBag.cpp
        LinkedBag.h
        LinkedBag340.cpp
        LinkedBagClient340.cpp
        Node.cpp
        Node.h)
