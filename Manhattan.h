//
// Created by Dansa on 10/12/2022.
//

#ifndef K_NEAREST_NEIGHBORS_MANHATTAN_H
#define K_NEAREST_NEIGHBORS_MANHATTAN_H

#include "Minkowski.h"


class Manhattan : public Minkowski {
private:
public:
    double distance(vector<double> v1, vector<double> v2, double p = 1) override;
};


#endif //K_NEAREST_NEIGHBORS_MANHATTAN_H
