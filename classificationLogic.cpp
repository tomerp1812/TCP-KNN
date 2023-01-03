//
// Created by Dansa on 31/12/2022.
//

#include "classificationLogic.h"



/**
 * This function checks if a string is a valid number
 *
 * @param str the string to check.
 *
 * @return true if the string is a number, and false if it is not.
 */
bool checkStr(string str) {
    //making a flag to the end of the string.
    str += '\0';
    string substring;
    //iterating over the string.
    for (char x: str) {
        if (x == ' ' || x == '\0') {
            if (!Database::checkIfNum(substring)) {
                return false;
            }
            //nullifies the substring and the flag.
            substring = "";
        } else {
            substring += x;
        }
    }
    return true;
}

/**
 * This function checks if a string is a positive number
 *
 * @param str the string to check.
 *
 * @return true if the string is a positive number, and false if it is not.
 */
bool isPositiveInteger(const string &s) {
    if (s.empty() || ((!isdigit(s[0])))) {
        return false;
    }

    char *p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

/**
 * This function calls an auxiliary function named "checkStr",
 * to check if the input is valid, and then adds the values from the user
 * to the end of the vector.
 * @return Vector of doubles.
 */
vector<double> createVec(string vec) {
    vector<double> v;
    double num;

    //input stream class to operate on strings.
    istringstream vStream(vec);
    //checking if the input is valid and returns a blank vector in accordance.
    if (!checkStr(vec)) {
        return v;
    }
    //adding values to the vector.
    while (vStream >> num) {
        v.push_back(num);
    }
    //removes all the elements from an unordered set and empties it.
    vStream.clear();
    return v;
}

/**
 * This function receives the classified file and the k (number of neighbors) and returns a
 * pointer to a Database object.
 * @param file - the file with the classified vectors
 * @param k - number of neighbors
 * @return A pointer to a Database object.
 */
Database *initializeDatabase(string file, int k) {
    //checks for the validation of the number of neighbors
    if (k <= 0) {
        cout << "oops! You must have a partner for tango!" << endl;
        exit(1);
    }
    return new Database(file, k);
}

/**
 * This function returns a pointer to a Distance object based on its given parameter.
 * Notice that the function returns a nullptr if the parameter it receives doesn't appeal
 * with any of the distance algorithms.
 * @param disAlg the distance algorithm which we want to create an object from
 * @return A pointer to a Distance object.
 */
Distance *chooseDis(const char *disAlg) {
    if (strcmp(disAlg, "AUC") == 0) {
        return new Euclidean();
    } else if (strcmp(disAlg, "MAN") == 0) {
        return new Manhattan();
    } else if (strcmp(disAlg, "CHB") == 0) {
        return new Chebyshev();
    } else if (strcmp(disAlg, "CAN") == 0) {
        return new Canberra();
    } else if (strcmp(disAlg, "MIN") == 0) {
        return new Minkowski();
    } else {
        return nullptr;
    }
}

/**
 * This function creates a vector, finds the classification of the vector using the
 * KNN algorithm, and prints the classification of the inserted vector.
 * @param dataBase a pointer to the database
 * @param dis the distance function to be used
 * @param vec the new inserted vector
 * @return a string with the new vector's classification
 */
string newVectorClassification(Database *dataBase, Distance *dis, string vec) {
    vector<double> v1 = createVec(vec);
    if (v1.empty()) {
        return "invalid input";
    }
    //check if the vector's size match the size of the vectors from the given file
    if (v1.size() != dataBase->getMData()->at(0).getVector().size()) {
        return "invalid input";
    }

    //find the classification of the vector using the KNN algorithm
    return dataBase->findKNN(*dis, v1);
}
