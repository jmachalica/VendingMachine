

#ifndef DRINK_H
#define DRINK_H

#include <iostream>

class Drink {

    const int id;
    const char *name = nullptr;
    const double price{0};
    static int id_auto;

    friend class VendingMachine;

    friend std::ostream &operator<<(std::ostream &os, const Drink *drink);

public:

    explicit Drink(const char *name = nullptr, double price = 0) : id{id_auto++}, price{price}, name{name} {}

    Drink(const Drink &) = delete;

    Drink &operator=(const Drink &) = delete;

};


#endif
