//
// Created by Sergey on 17.02.2024.
//

#include <valarray>
#include "Polynomial.h"

Polynomial::~Polynomial() {
    head = nullptr;
}

void Polynomial::addMonom(int coeff, int degrees) {

    Monomial *newMonom = new Monomial(coeff, degrees);

    if (head == nullptr || degrees > head->degrees) {
        newMonom->next = head;
        head = newMonom;
    } else {
        Monomial *tmp = head;
        Monomial *pr = nullptr;

        while (tmp != nullptr && tmp->degrees > degrees) {
            pr = tmp;
            tmp = tmp->next;
        }
        if (tmp != nullptr && tmp->degrees == degrees) {
            tmp->coef += coeff;
            if (tmp->coef == 0) {
                if (pr == nullptr) {
                    head = tmp->next;
                } else {
                    pr->next = tmp->next;
                }
            }
        } else {
            newMonom->next = tmp;
            if (pr == nullptr) {
                head = newMonom;
            } else {
                pr->next = newMonom;
            }
        }
    }
}


Polynomial::Polynomial(string polyStr) {
    head = nullptr;
    if (polyStr == "0") {
        return;
    }

    int coef = 0;
    int sign = 1;
    string numstr = "";
    string degs = "000";

    for (size_t i = 0; i <= polyStr.length(); i++) {
        if (i == polyStr.length() || polyStr[i] == '+' || polyStr[i] == '-') {
            if (!numstr.empty()) {
                coef = stoi(numstr) * sign;
                addMonom(coef, stoi(degs));
                numstr = "";
                degs = "000";
            }
            if (i < polyStr.length() && polyStr[i] == '-') {
                sign = -1;
            } else {
                sign = 1;
            }
        } else if (isdigit(polyStr[i])) {
            numstr += polyStr[i];
        } else if (polyStr[i] == 'x' || polyStr[i] == 'y' || polyStr[i] == 'z') {
            if (numstr.empty() && (i == 0 || polyStr[i - 1] != '^'))
                numstr = "1";
            size_t pos;
            if (polyStr[i] == 'x') {
                pos = 0;
            } else if (polyStr[i] == 'y') {
                pos = 1;
            } else {
                pos = 2;
            }
            i++;
            if (i < polyStr.length() && polyStr[i] == '^') {
                i++;
                string exp = "";
                while (i < polyStr.length() && isdigit(polyStr[i])) {
                    exp += polyStr[i++];
                }
                i--;
                if (exp.empty()) {
                    degs[pos] = '1';
                } else {
                    degs[pos] = exp[0];
                }
            } else {
                degs[pos] = '1';
                i--;
            }
        }
    }
}


// --------------- Iterator -------------

Polynomial::Monomial &Polynomial::Iterator::operator*() {
    return *cur;
}

Polynomial::Iterator &Polynomial::Iterator::operator++() {
    if (cur) {
        cur = cur->next;
    }
    return *this;
}


bool Polynomial::Iterator::operator!=(const Iterator &other) {
    return cur != other.cur;
}

// -------------------------------------

Polynomial::Iterator Polynomial::begin() {
    return Iterator(head);
}

Polynomial::Iterator Polynomial::end() {
    return Iterator(nullptr);
}

void Polynomial::print() {
    if (head == nullptr) {
        cout << "0";
        return;
    }

    for (auto i = begin(); i != end(); ++i) {

        Monomial monom = *i;
        //cout << endl << monom.degrees << endl;
        if (i != begin() && monom.coef > 0) {
            cout << "+";
        }

        if (monom.coef != 1) {
            cout << monom.coef;
        }

        int degs = monom.degrees;

        int degX = degs / 100;
        int degY = (degs - degX * 100) / 10;
        int degZ = degs % 10;


        if (degX > 0) {
            if (degX == 1) {
                cout << "x";
            } else {
                cout << "x^" << degX;
            }
        }

        if (degY > 0) {
            if (degY == 1) {
                cout << "y";
            } else {
                cout << "y^" << degY;
            }
        }

        if (degZ > 0) {
            if (degZ == 1) {
                cout << "z";
            } else {
                cout << "z^" << degZ;
            }
        }
    }
}

Polynomial Polynomial::operator+(const Polynomial &other) const {
    Polynomial res;
    Monomial *mon1 = this->head;
    Monomial *mon2 = other.head;
    while (mon1 != nullptr || mon2 != nullptr) {
        if (mon1 == nullptr) {
            res.addMonom(mon2->coef, mon2->degrees);
            mon2 = mon2->next;
        } else if (mon2 == nullptr) {
            res.addMonom(mon1->coef, mon1->degrees);
            mon1 = mon1->next;
        } else if (mon1->degrees == mon2->degrees) {
            int newC = mon1->coef + mon2->coef;
            if (newC != 0) {
                res.addMonom(newC, mon1->degrees);
            }
            mon1 = mon1->next;
            mon2 = mon2->next;
        } else if (mon1->degrees > mon2->degrees) {
            res.addMonom(mon1->coef, mon1->degrees);
            mon1 = mon1->next;
        } else {
            res.addMonom(mon2->coef, mon2->degrees);
            mon2 = mon2->next;
        }
    }

    return res;
}

Polynomial Polynomial::operator*(int c) const {
    Polynomial res;
    if (c == 0) {
        return res;
    }
    for (Monomial *cur = head; cur != nullptr; cur = cur->next) {
        res.addMonom((cur->coef) * c, cur->degrees);
    }
    return res;
}

Polynomial Polynomial::operator*(const Polynomial &other) const {
    Polynomial res;
    for (Monomial *cur1 = head; cur1 != nullptr; cur1 = cur1->next) {
        for (Monomial *cur2 = other.head; cur2 != nullptr; cur2 = cur2->next) {
            res.addMonom((cur1->coef) * (cur2->coef), (cur1->degrees) + (cur2->degrees));
        }
    }
    return res;
}

Polynomial Polynomial::operator-(const Polynomial &other) const {
    Polynomial res;
    Polynomial ot = other * (-1);
    res = this->operator+(ot);
    return res;
}

bool Polynomial::operator==(const Polynomial &other) const {
    Monomial *cur1 = head;
    Monomial *cur2 = other.head;

    while (cur1 != nullptr && cur2 != nullptr) {
        if (((cur1->degrees) != (cur2->degrees)) || ((cur1->coef) != (cur2->coef))) {
            return false;
        }

        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    if (cur1 == nullptr && cur2 == nullptr) {
        return true;
    }
    return false;
}

double Polynomial::calculate(double x, double y, double z) const{
    double result = 0;
    Monomial *current = head;
    while (current != nullptr) {
        int termValue = current->coef;
        termValue *= pow(x, (current->degrees) / 100);
        termValue *= pow(y, (current->degrees % 100) / 10);
        termValue *= pow(z, (current->degrees % 10));
        result += termValue;
        current = current->next;
    }
    return result;
}

