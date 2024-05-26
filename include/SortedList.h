//
// Created by Sergey on 13.05.2024.
//

#include "iostream"
#include <list>
#include <string>
#include "Polynomial.h"

using namespace std;

class SortedList {
private:
    list<pair<string, Polynomial>> table;

public:
    void addPol(const string &name, Polynomial &pol);

    void removePol(const string &name);

    Polynomial *findPol(const string &name);

    void printTable();
};