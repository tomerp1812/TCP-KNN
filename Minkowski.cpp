//
// Created by Dansa on 10/12/2022.
//

#include "Minkowski.h"

/**
 * This function calculates the distance between two vectors using the "Minkowski distance" formula.
 * @see <a href="https://en.wikipedia.org/wiki/Minkowski_distance">more info about it</a>
 * @param v1 first vector.
 * @param v2 second vector.
 * @return distance between two vectors.
 */
double Minkowski::distance(vector<double> v1, vector<double> v2, double p) {
    double sum = 0;
    for (size_t i = 0; i < v1.size(); i++) {
        sum += pow(abs(v1[i] - v2[i]), p);
    }
    return pow(sum, 1.0 / p);
}

