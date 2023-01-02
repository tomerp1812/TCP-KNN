cmake_minimum_required(VERSION 3.20)
project(project)

set(CMAKE_CXX_STANDARD 11)


add_executable(project
       Canberra.h Canberra.cpp Catalog.h Catalog.cpp Chebyshev.h Chebyshev.cpp Database.cpp Database.h
         Distance.cpp Distance.h Euclidean.cpp Euclidean.h Server.cpp Manhattan.cpp Manhattan.h Minkowski.cpp
        Minkowski.h Server.h classificationLogic.cpp classificationLogic.h)

add_executable(client
        client.cpp)