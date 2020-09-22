cmake_minimum_required(VERSION 3.17)
project(Farkle_Game_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Farkle_Game_Project
        dice.cpp
        dice.h
        Farkle.cpp
        gameEngine.cpp
        gameEngine.h
        player.cpp
        player.h)
