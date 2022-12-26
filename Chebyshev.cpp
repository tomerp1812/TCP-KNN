//
// Created by Tomer on 10/12/2022.
//

#include "Chebyshev.h"

/**
 * This function calculates the distance between two vectors using the "Chebyshev distance" formula.
 * @see <a href="https://en.wikipedia.org/wiki/Chebyshev_distance">more info about it</a>
 * @param v1 first vector.
 * @param v2 second vector.
 * @return distance between two vectors.
 */
double Chebyshev::distance(vector<double> v1, vector<double> v2, double p) {
    double dist = 0, current;
    for (size_t i = 0; i < v1.size(); i++) {
        current = abs(v1[i] - v2[i]);
        //taking the maximum value.
        if (current > dist) {
            dist = current;
        }
    }
    return dist;
}
