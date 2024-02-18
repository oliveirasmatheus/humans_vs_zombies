cmake_minimum_required(VERSION 3.26)
project(CPPAss4)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPPAss4 main.cpp
        City.cpp
        GameSpecs.cpp
        Human.cpp
        Organism.cpp
        Zombie.cpp)
