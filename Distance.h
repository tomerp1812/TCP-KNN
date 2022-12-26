//
// Created by Tomer on 10/12/2022.
//
#ifndef DISTANCE_H
#define DISTANCE_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;

class Distance {
private:
public:
    virtual double distance(vector<double> v1, vector<double> v2, double p = 1) = 0;
};


#endif