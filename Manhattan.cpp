//
// Created by Dansa on 10/12/2022.
//

#include "Manhattan.h"


/**
 * This function calculates the distance between two vectors using the "Manhattan distance" formula.
 * @see <a href="https://en.wikipedia.org/wiki/Taxicab_geometry">more info about it</a>
 * @param v1 first vector.
 * @param v2 second vector.
 * @return distance between two vectors.
 */
double Manhattan::distance(vector<double> v1, vector<double> v2, double p) {
    //This is a private case of the Minkowski distance formula with p=1.
    return Minkowski::distance(v1, v2, p);
}
