//
// Created by Sergey on 26.05.2024.
//

#include <vector>
#include <string>
#include <list>
#include "Polynomial.h"

using namespace std;

struct HashFunc1 {
    int operator()(const string &key) {
        int hash = 0;
        for (char ch: key) {
            hash = (hash + ch) % 100;
        }
        return hash;
    }
};

struct HashFunc2 {
    int operator()(const string &key) {
        int hash = 0;
        for (char ch: key) {
            hash = (hash * 11 + ch) % 100;
        }
        return hash;
    }
};

template<typename HashFunc>
class HashTable {
private:
    static const int TABLE_SIZE = 100;
    vector<list<pair<string, Polynomial>>> table;
    HashFunc hashFunction;

public:
    HashTable() : table(TABLE_SIZE) {}

    void addPol(const string &name, Polynomial &polynomial);

    void removePol(const string &name);

    Polynomial *findPol(const string &name);

    void print();
};


template<typename HashFunc>
void HashTable<HashFunc>::addPol(const string &name, Polynomial &polynomial) {
    int i = hashFunction(name) % TABLE_SIZE;
    for (auto &st: table[i]) {
        if (st.first == name) {
            st.second = polynomial;
            return;
        }
    }
    table[i].emplace_back(name, polynomial);
}

template<typename HashFunc>
void HashTable<HashFunc>::removePol(const string &name) {
    int i = hashFunction(name) % TABLE_SIZE;
    for (auto it = table[i].begin(); it != table[i].end(); it++) {
        if (it->first == name) {
            table[i].erase(it);
            return;
        }
    }
}

template<typename HashFunc>
Polynomial *HashTable<HashFunc>::findPol(const string &name) {
    int i = hashFunction(name) % TABLE_SIZE;
    for (auto &st: table[i]) {
        if (st.first == name) {
            return &st.second;
        }
    }
    return nullptr;
}

template<typename HashFunc>
void HashTable<HashFunc>::print() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[i].empty()) {
            for (auto &st: table[i]) {
                cout << st.first << ": ";
                st.second.print();
                cout << "; ";
            }
            cout << endl;
        }
    }
}


