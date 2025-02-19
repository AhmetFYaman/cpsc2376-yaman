#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include "Val.h"
 
 
int main() {
    printCharByChar("Give me double (1-9): ");
    double x = getValidNumber<double>(1,9);
 
    return 0;
}