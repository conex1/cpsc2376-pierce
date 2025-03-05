#include "Fraction.h"
#include <stdexcept>
#include <cmath>

Fraction::Fraction() : num(0), den(1) {}

Fraction::Fraction(int n, int d) : num(n), den(d) {
    if (den == 0) throw std::invalid_argument("Denominator cannot be zero");
    simplify();
}

int Fraction::getNumerator() const { return num; }
int Fraction::getDenominator() const { return den; }

void Fraction::setNumerator(int n) {
    num = n;
    simplify();
}

void Fraction::setDenominator(int d) {
    if (d == 0) throw std::invalid_argument("Denominator cannot be zero");
    den = d;
    simplify();
}

void Fraction::simplify() {
    if (den == 0) throw std::invalid_argument("Denominator cannot be zero");
    if (den < 0) {
        num = -num;
        den = -den;
    }
    int a = std::abs(num);
    int b = den;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;
    num /= gcd;
    den /= gcd;
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    int new_num = lhs.num * rhs.den + rhs.num * lhs.den;
    int new_den = lhs.den * rhs.den;
    return Fraction(new_num, new_den);
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    int new_num = lhs.num * rhs.den - rhs.num * lhs.den;
    int new_den = lhs.den * rhs.den;
    return Fraction(new_num, new_den);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    int new_num = lhs.num * rhs.num;
    int new_den = lhs.den * rhs.den;
    return Fraction(new_num, new_den);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    if (rhs.num == 0) throw std::invalid_argument("Division by zero");
    int new_num = lhs.num * rhs.den;
    int new_den = lhs.den * rhs.num;
    return Fraction(new_num, new_den);
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.num << "/" << f.den;
    return os;
}