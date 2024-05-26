//
// Created by Sergey on 13.05.2024.
//

#include "LinearMas.h"


LinearMas::LinearMas() : size(0) {}

void LinearMas::addPol(const string &name, Polynomial &polynomial) {
    for (int i = 0; i < size; i++) {
        if (table[i].first == name) {
            table[i].second = polynomial;
            return;
        }
    }

    if (size < MAX_SIZE) {
        table[size] = make_pair(name, polynomial);
        size++;
    } else {
        throw out_of_range("Size out of range");
    }
}

void LinearMas::removePol(const string &name) {
    for (int i = 0; i < size; i++) {
        if (table[i].first == name) {
            for (int j = i; j < size - 1; j++) {
                table[j] = table[j + 1];
            }
            size--;
            return;
        }
    }
}

Polynomial *LinearMas::findPol(const string &name) {
    for (int i = 0; i < size; i++) {
        if (table[i].first == name) {
            return &table[i].second;
        }
    }
    return nullptr;
}

void LinearMas::printTable() {
    for (int i = 0; i < size; i++) {
        cout << table[i].first << ": ";
        table[i].second.print();
        cout << endl;
    }
}