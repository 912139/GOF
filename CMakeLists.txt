cmake_minimum_required(VERSION 3.21)
project(HW_1_SBomber)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW_1_SBomber
        Bomb.cpp
        Bomb.h
        DestroyableGroundObject.h
        DynamicObject.h
        GameObject.h
        Ground.cpp
        Ground.h
        House.cpp
        House.h
        LevelGUI.cpp
        LevelGUI.h
        MyTools.cpp
        MyTools.h
        Plane.cpp
        Plane.h
        SBomber.cpp
        SBomber.h
        SBomberProject.cpp
        Tank.cpp
        Tank.h)
