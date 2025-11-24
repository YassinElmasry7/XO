cmake_minimum_required(VERSION 4.0)
project(XO)

set(CMAKE_CXX_STANDARD 14)

include_directories(XO)

add_executable(XO
        XO/BoardGame_Classes.h
        XO/XO.cpp
        XO/XO_Classes.cpp
        XO/XO_Classes.h)
