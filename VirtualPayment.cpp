
#include "VirtualPayment.h"
#include <iostream>
#include <algorithm>
#include <cctype>

bool VirtualPayment::validCode(std::string code, const int length) const {
    //remove returns string end with moved white spaces, then white spaces are deleted
    code.erase(std::remove_if(code.begin(), code.end(), [](unsigned char c) { return std::isblank(c); }), code.end());
    if (code.length() != length)return false;
    for (int i = 0; i < code.length(); i++) {

        if (code[i] < '0' || code[i] > '9')return false;

    }
    return true;


}
