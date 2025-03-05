#include "MixedFraction.h"
#include <cmath>

MixedFraction::MixedFraction(int whole, int n, int d)
    : Fraction(whole* d + (whole < 0 ? -n : n), d) {
    if (d == 0) throw std::invalid_argument("Denominator cannot be zero");
}

MixedFraction::MixedFraction(const Fraction& f) : Fraction(f) {}

std::ostream& operator<<(std::ostream& os, const MixedFraction& mf) {
    int num = mf.getNumerator();
    int den = mf.getDenominator();

    if (den == 1) {
        os << num;
        return os;
    }

    if (num == 0) {
        os << "0";
        return os;
    }

    bool is_negative = (num < 0);
    int abs_num = abs(num);
    int whole = abs_num / den;
    int remainder = abs_num % den;

    if (is_negative) {
        os << "-";
    }

    if (whole != 0) {
        os << whole;
    }

    if (remainder != 0) {
        if (whole != 0) {
            os << " ";
        }
        os << remainder << "/" << den;
    }
    else if (whole == 0) {
        os << "0";
    }

    return os;
}