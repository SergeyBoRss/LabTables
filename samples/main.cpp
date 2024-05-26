#include "LinearMas.h"
#include "LinearList.h"
#include "SortedList.h"
#include "AVLTree.h"
#include "HashTable.h"

void addPolynomial(const string &key, Polynomial &pol, LinearMas &lm, LinearList &ll, SortedList &sl,
                   AVLTree &avl, HashTable<HashFunc1> &ht1, HashTable<HashFunc2> &ht2) {
    lm.addPol(key, pol);
    ll.addPol(key, pol);
    sl.addPol(key, pol);
    avl.addPol(key, pol);
    ht1.addPol(key, pol);
    ht2.addPol(key, pol);
}

void removePolynomial(const string &key, LinearMas &lm, LinearList &ll, SortedList &sl, AVLTree &avl,
                      HashTable<HashFunc1> &ht1, HashTable<HashFunc2> &ht2) {
    lm.removePol(key);
    ll.removePol(key);
    sl.removePol(key);
    avl.removePol(key);
    ht1.removePol(key);
    ht2.removePol(key);
}

Polynomial *
findPolynomial(const string &key, int tableType, LinearMas &lm, LinearList &ll, SortedList &sl, AVLTree &avl,
               HashTable<HashFunc1> &ht1, HashTable<HashFunc2> &ht2) {
    switch (tableType) {
        case 1:
            return lm.findPol(key);
        case 2:
            return ll.findPol(key);
        case 3:
            return sl.findPol(key);
        case 4:
            return avl.findPol(key);
        case 5:
            return ht1.findPol(key);
        case 6:
            return ht2.findPol(key);
        default:
            return nullptr;
    }
}

void printTable(int tableType, LinearMas &lm, LinearList &ll, SortedList &sl, AVLTree &avl, HashTable<HashFunc1> &ht1,
                HashTable<HashFunc2> &ht2) {
    switch (tableType) {
        case 1:
            lm.printTable();
            break;
        case 2:
            ll.printTable();
            break;
        case 3:
            sl.printTable();
            break;
        case 4:
            avl.print();
            break;
        case 5:
            ht1.print();
            break;
        case 6:
            ht2.print();
            break;
        default:
            break;
    }
}

int main() {
    LinearMas lm;
    LinearList ll;
    SortedList sl;
    AVLTree avl;
    HashTable<HashFunc1> ht1;
    HashTable<HashFunc2> ht2;

    while (true) {
        cout << "1. Add polynomial\n2. Remove polynomial\n3. Find polynomial\n4. Print table\n5. Exit\n";
        int choice;
        cin >> choice;
        if (choice == 5) break;

        string key, polyStr;
        Polynomial *pol;
        int tableType;
        switch (choice) {
            case 1:
                cout << "Enter key:";
                cin >> key;
                cout << "Enter polynomial:";
                cin.ignore();
                getline(cin, polyStr);
                pol = new Polynomial(polyStr);
                addPolynomial(key, *pol, lm, ll, sl, avl, ht1, ht2);
                break;
            case 2:
                cout << "Enter key:";
                cin >> key;
                removePolynomial(key, lm, ll, sl, avl, ht1, ht2);
                break;
            case 3:
                cout << "Enter key:";
                cin >> key;
                cout
                        << "Select table to search (1: LinearMas, 2: LinearList, 3: SortedList, 4: AVLTree, 5: HashTable1, 6: HashTable2):";
                cin >> tableType;
                pol = findPolynomial(key, tableType, lm, ll, sl, avl, ht1, ht2);
                if (pol) {
                    cout << "Found polynomial:";
                    pol->print();
                    cout << endl;
                } else {
                    cout << "Polynomial not found" << endl;
                }
                break;
            case 4:
                cout
                        << "Select table to print (1: LinearMas, 2: LinearList, 3: SortedList, 4: AVLTree, 5: HashTable1, 6: HashTable2):";
                cin >> tableType;
                printTable(tableType, lm, ll, sl, avl, ht1, ht2);
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }

    return 0;

}