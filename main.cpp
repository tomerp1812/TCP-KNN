//
// Created by Tomer on 01/12/2022.
//

#include "Database.h"
#include "Distance.h"
#include "Euclidean.h"
#include "Manhattan.h"
#include "Chebyshev.h"
#include "Canberra.h"
#include "Minkowski.h"
#include "cstring"

/**
 * It checks if a string is a valid number
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
 * This function calls an auxiliary function named "checkStr",
 * to check if the input is valid, and then adds the values from the user
 * to the end of the vector.
 * @return Vector of doubles.
 */
vector<double> createVec() {
    //initialization.
    string str;
    vector<double> v;
    double num;
    //extracts characters from cin and stores them into str until the delimitation character delim is found.
    getline(cin, str);
    //input stream class to operate on strings.
    istringstream vStream(str);
    //checking if the input is valid and returns a blank vector in accordance.
    if (!checkStr(str)) {
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
 * This function receives the command line arguments and returns a pointer to a Database object.
 * @param argv the command line arguments
 * @return A pointer to a Database object.
 */
Database *initializeDatabase(char const *argv[]) {
    int k = stoi(argv[1]);
    string dest = argv[2];
    //checks for the validation of the number of neighbors
    if (k <= 0) {
        cout << "oops! You must have a partner for tango!" << endl;
        exit(1);
    }
    return new Database(dest, k);
}

/**
 * This function returns a pointer to a Distance object based on its given parameter.
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
        cout << "Wrong input! None valid distance calculation." << endl;
        exit(1);
    }
}

/**
 * This function creates a vector, finds the classification of the vector using the
 * KNN algorithm, and prints the classification of the inserted vector.
 * @param dataBase a pointer to the database
 * @param dis the distance function to be used
 */
void newVectorClassification(Database *dataBase, Distance *dis) {
    while (true) {
        vector<double> v1 = createVec();
        if (v1.empty()) {
            cout << "Wrong input! Try again" << endl;
            continue;
        }
        //check if the vector's size match the size of the vectors from the given file
        if (v1.size() != dataBase->getMData()->at(0).getVector().size()) {
            cout << "Unmatched size! Try again" << endl;
            continue;
        }

        //find the classification of the vector using the KNN algorithm
        dataBase->findKNN(*dis, v1);
    }
}

/**
 * The main function creates a Database object, and then get a new inserted vector.
 * It then finds the k nearest neighbors of that vector and classified the inserted vector
 * to be of the same classification as the biggest group inside the k nearest neighbors.
 * @param argc the number of arguments
 * @param argv
 * @return The name of the closest point to the input vector.
 */
int main(int argc, char const *argv[]) {
    //initialize the database
    auto *dataBase = initializeDatabase(argv);

    //choose the distance algorithm
    const char *disAlg = argv[3];
    Distance *dis = chooseDis(disAlg);

    //classified a new inserted vector
    newVectorClassification(dataBase, dis);

    return 0;
}

