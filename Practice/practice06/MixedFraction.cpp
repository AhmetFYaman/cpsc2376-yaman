#include "MixedFraction.h"

MixedFraction::MixedFraction(int whole, int n, int d) : Fraction(whole * d + n, d) {
    if (d == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
}

MixedFraction::MixedFraction(const Fraction& frac) : Fraction(frac) {}

std::ostream& operator<<(std::ostream& os, const MixedFraction& mFrac) {
    int whole = mFrac.getNumerator() / mFrac.getDenominator();
    int remainderNum = mFrac.getNumerator() % mFrac.getDenominator();
    int den = mFrac.getDenominator();

    if (whole != 0) {
        os << whole << " ";
    }

    if(remainderNum < 0 || den < 0) {
        remainderNum = std::abs(remainderNum);
        den = std::abs(den);
    }

    os << remainderNum << "/" << den;
    return os;
}