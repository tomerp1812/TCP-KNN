cmake_minimum_required(VERSION 3.23)
project(project)

set(CMAKE_CXX_STANDARD 11)


add_executable(project
       Canberra.h Canberra.cpp Catalog.h Catalog.cpp Chebyshev.h Chebyshev.cpp Database.cpp Database.h
         Distance.cpp Distance.h Euclidean.cpp Euclidean.h main.cpp Manhattan.cpp Manhattan.h Minkowski.cpp
        Minkowski.h)
