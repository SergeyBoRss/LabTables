//
// Created by Sergey on 17.02.2024.
//
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "iostream"

using namespace std;

class Polynomial {
private:
    struct Monomial {
        int coef;
        int degrees;
        Monomial *next;

        Monomial(int c, int deg) : coef(c), degrees(deg), next(nullptr) {}
    };

    Monomial *head;

public:
    Polynomial() : head(nullptr) {};

    Polynomial(string pol);

    ~Polynomial();

    void addMonom(int coeff, int degrees);

    class Iterator {
    private:
        Monomial *cur;
    public:
        Iterator(Monomial *cur = nullptr) : cur(cur) {}

        Monomial &operator*();

        Iterator &operator++();

        bool operator!=(const Iterator &other);
    };

    Iterator begin();

    Iterator end();

    void print();

    Polynomial operator+(const Polynomial &other) const;

    Polynomial operator-(const Polynomial &other) const;

    Polynomial operator*(const Polynomial &other) const;

    Polynomial operator*(int c) const;

    bool operator==(const Polynomial &other) const;

    double calculate(double x, double y, double z) const;
};

#endif




