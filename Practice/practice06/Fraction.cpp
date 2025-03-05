#include "Fraction.h"


Fraction::Fraction() : num(0), den(1) {}


Fraction::Fraction(int n, int d) : num(n), den(d) {
    if (den == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    simplify();
}


int Fraction::getNumerator() const { return num; }
int Fraction::getDenominator() const { return den; }


void Fraction::setNumerator(int n) {
    num = n;
    simplify();
}

void Fraction::setDenominator(int d) {
    if (d == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    den = d;
    simplify();
}


void Fraction::simplify() {
    if (den == 0) return;

    int a = num, b = den;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;

    num /= gcd;
    den /= gcd;


    if (den < 0) {
        num = -num;
        den = -den;
    }
}


Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    int newNum = lhs.num * rhs.den + rhs.num * lhs.den;
    int newDen = lhs.den * rhs.den;
    return Fraction(newNum, newDen);
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    int newNum = lhs.num * rhs.den - rhs.num * lhs.den;
    int newDen = lhs.den * rhs.den;
    return Fraction(newNum, newDen);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    int newNum = lhs.num * rhs.num;
    int newDen = lhs.den * rhs.den;
    return Fraction(newNum, newDen);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    if (rhs.num == 0) {
        throw std::invalid_argument("Division by zero.");
    }
    int newNum = lhs.num * rhs.den;
    int newDen = lhs.den * rhs.num;
    return Fraction(newNum, newDen);
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.num << "/" << frac.den;
    return os;
}