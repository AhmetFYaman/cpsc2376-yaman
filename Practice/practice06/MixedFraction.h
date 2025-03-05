#pragma once

#include "Fraction.h"

class MixedFraction : public Fraction {
public:
    
    MixedFraction(int whole, int n, int d); 
    MixedFraction(const Fraction& frac); 

   
    friend std::ostream& operator<<(std::ostream& os, const MixedFraction& mFrac);
};

