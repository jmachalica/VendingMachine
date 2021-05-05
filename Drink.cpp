
#include "Drink.h"
#include <iostream>


int Drink::id_auto{};

std::ostream &operator<<(std::ostream &os, const Drink *drink) {
    return os << drink->name << "  |  price:" << drink->price;
}
