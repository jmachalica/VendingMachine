
#ifndef VIRTUALPAYMENT_H
#define VIRTUALPAYMENT_H

#include "Payment.h"
#include <iostream>
//virtual class for card and blik payments

class VirtualPayment : public Payment {
protected:
    bool validCode(std::string, int length) const;
    explicit VirtualPayment(const char *name) : Payment(name) {}

};


#endif
