//
// Created by Sergey on 13.05.2024.
//

#include "iostream"
#include <string>
#include "Polynomial.h"

using namespace std;

class LinearMas {
private:
    static const int MAX_SIZE = 100;
    pair<string, Polynomial> table[MAX_SIZE];
    int size;

public:
    LinearMas();

    void addPol(const string &name, Polynomial &pol);

    void removePol(const string &name);

    Polynomial *findPol(const string &name);

    void printTable();
};
