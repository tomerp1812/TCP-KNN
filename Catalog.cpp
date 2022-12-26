//
// Created by Tomer on 06/12/2022.
//

#include "Catalog.h"

namespace classifiedCatalog {
    /**
     * constructor of Catalog. sets a default distance to 0 because we didn't check
     * distances from any vector yet.
     * @param name name of one of the kinds of the catalog.
     * @param vector a vector.
     */
    Catalog::Catalog(string name, vector<double> vector) {
        setName(name);
        setVector(vector);
        setDistance(0);
    }

    /**
     * setter of name.
     * @param name name of the kinds of the catalog.
     */
    void Catalog::setName(string name) {
        this->m_name = name;
    }

    /**
     * setter of vector
     * @param vector a vector.
     */
    void Catalog::setVector(vector<double> vector) {
        this->m_vector = vector;
    }

    /**
     * setter of distance.
     * @param distance distance between this vector and the new coming vector
     */
    void Catalog::setDistance(double distance) {
        this->m_distance = distance;
    }

    /**
     * getter of name.
     * @return string.
     */
    string Catalog::getName() {
        return this->m_name;
    }

    /**
     * getter of vector.
     * @return vector<double>
     */
    vector<double> Catalog::getVector() {
        return this->m_vector;
    }

    /**
     * getter of distance.
     * @return int.
     */
    double Catalog::getDistance() {
        return this->m_distance;
    }
}