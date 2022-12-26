//
// Created by Dansa on 06/12/2022.
//

#ifndef K_NEAREST_NEIGHBORS_DATABASE_H
#define K_NEAREST_NEIGHBORS_DATABASE_H


#include "Distance.h"
#include "Catalog.h"
#include "fstream"


using namespace classifiedCatalog;

class Database {
private:
    string m_file;
    vector<Catalog> m_data;
    int m_k;
public:
    Database(string fileName, int k);

    int getK() const;

    void setK(int k);

    vector<Catalog> *getMData();

    Catalog *setCatalog(string str);

    static bool checkIfNum(string substring);

    void setData();

    void add(string newName, vector<double> unclassifiedVector);

    void findKNN(Distance &d, vector<double> unclassifiedVector);

    string classifyVector();

    bool compare(int i, int j);

    void swap(int i, int j);

    int partition(int left, int right, int pivot);

    void select(int left, int right);
};

#endif //K_NEAREST_NEIGHBORS_DATABASE_H
