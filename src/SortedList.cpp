//
// Created by Sergey on 13.05.2024.
//
#include "SortedList.h"

void SortedList::addPol(const string &name, Polynomial &polynomial) {
    for (auto id = table.begin(); id != table.end(); id++) {
        if (id->first == name) {
            id->second = polynomial;
            return;
        } else if (id->first > name) {
            table.insert(id, make_pair(name, polynomial));
            return;
        }
    }
    table.emplace_back(name, polynomial);
}

void SortedList::removePol(const string &name) {
    for (auto id = table.begin(); id != table.end(); id++) {
        if (id->first == name) {
            table.erase(id);
            return;
        }
    }
}

Polynomial *SortedList::findPol(const string &name) {
    for (auto &st: table) {
        if (st.first == name) {
            return &st.second;
        }
    }
    return nullptr;
}

void SortedList::printTable() {
    for (auto &st: table) {
        cout << st.first << ": ";
        st.second.print();
        cout << endl;
    }
}