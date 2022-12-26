//
// Created by Dansa on 10/12/2022.
//

#ifndef K_NEAREST_NEIGHBORS_EUCLIDEAN_H
#define K_NEAREST_NEIGHBORS_EUCLIDEAN_H

#include "Minkowski.h"

class Euclidean : public Minkowski {
private:
public:
    double distance(vector<double>, vector<double>, double p = 1) override;

};


#endif //K_NEAREST_NEIGHBORS_EUCLIDEAN_H

