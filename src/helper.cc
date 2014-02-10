// helper.cc
// Some useful functions
// Teemu Mäkinen <culkah@gmail.com> 2014

#include <cmath>
#include "helper.h"

int stringToInt(const std::string &str) {
    int result = 0;
    for (unsigned int i = str.length() - 1; i >= 0; --i) {
        result += (str[i] * pow(10, str.length() - i - 1));
    }
    return result;
}
