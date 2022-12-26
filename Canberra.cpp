//
// Created by Tomer on 10/12/2022.
//

#include "Canberra.h"

/**
 * This function calculates the distance between two vectors using the "Canberra distance" formula.
 * @see <a href="https://en.wikipedia.org/wiki/Canberra_distance">more info about it</a>
 * @param v1 first vector.
 * @param v2 second vector.
 * @return distance between two vectors.
 */
double Canberra::distance(vector<double> v1, vector<double> v2, double p) {
    double dist = 0;
    for (size_t i = 0; i < v1.size(); i++) {
        //preventing a deviation by 0
        if (v1[i] + v2[i] == 0) {
            return 0;
        }
        dist += (abs(v1[i] - v2[i]) / (v1[i] + v2[i]));
    }
    return dist;
}
