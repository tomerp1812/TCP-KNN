//
// Created by Tomer on 06/12/2022.
//

#ifndef WORKS_IN_C___CATALOG_H
#define WORKS_IN_C___CATALOG_H

#include "Distance.h"

namespace classifiedCatalog {
    class Catalog {
    private:
        string m_name;
        vector<double> m_vector;
        double m_distance;
    public:
        Catalog(string name, vector<double> vector);

        void setName(string name);

        void setVector(vector<double> vector);

        void setDistance(double distance);

        string getName();

        vector<double> getVector();

        double getDistance();
    };
}


#endif //WORKS_IN_C___CATALOG_H
