//
// Created by Sergey on 13.05.2024.
//

#include "LinearList.h"

void LinearList::addPol(const string &name, Polynomial &polynomial) {
    for (auto &st: table) {
        if (st.first == name) {
            st.second = polynomial;
            return;
        }
    }
    table.emplace_back(name, polynomial);
}

void LinearList::removePol(const string &name) {
    for (auto id = table.begin(); id != table.end(); id++) {
        if (id->first == name) {
            table.erase(id);
            return;
        }
    }
}

Polynomial *LinearList::findPol(const string &name) {
    for (auto &st: table) {
        if (st.first == name) {
            return &st.second;
        }
    }
    return nullptr;
}

void LinearList::printTable() {
    for (auto &st: table) {
        cout << st.first << ": ";
        st.second.print();
        cout << endl;
    }
}
