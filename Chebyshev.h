//
// Created by Tomer on 10/12/2022.
//

#ifndef MAIN_CPP_CHEBYSHEV_H
#define MAIN_CPP_CHEBYSHEV_H

#include "Distance.h"

class Chebyshev : public Distance {
private:
public:
    double distance(vector<double> v1, vector<double> v2, double p = 1) override;
};


#endif //MAIN_CPP_CHEBYSHEV_H
