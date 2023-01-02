//
// Created by Dansa on 31/12/2022.
//

#ifndef PROJECT_CLASSIFICATIONLOGIC_H
#define PROJECT_CLASSIFICATIONLOGIC_H

#include "Database.h"
#include "Distance.h"
#include "Euclidean.h"
#include "Manhattan.h"
#include "Chebyshev.h"
#include "Canberra.h"
#include "Minkowski.h"
#include "cstring"

bool checkStr(string str);
vector<double> createVec();
Database *initializeDatabase(string file, int k);
Distance *chooseDis(const char *disAlg);
string newVectorClassification(Database *dataBase, Distance *dis, string vec);
bool isPositiveInteger(const string &s);

#endif //PROJECT_CLASSIFICATIONLOGIC_H
