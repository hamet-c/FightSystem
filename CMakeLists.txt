cmake_minimum_required(VERSION 3.14)
project(CS_Final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS_Final
        Attack.cpp
        Attack.h
        Fighting.cpp
        Player.cpp
        Player.h
        Players.cpp
        Players.h
        Game.cpp
        Intro.h
        Game.h
        Attacks.cpp
        Attacks.h
        WeaponChoice.h
        SwordArt.h
        TrialOne.h
        TrialTwo.h
        "TrialThree.h"
        TrialThree.cpp
        FinalBoss.h
        FinalBoss.cpp)

