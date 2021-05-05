//
// Created by hp on 2020-12-11.
//

#ifndef CARD_H
#define CARD_H

#include "Payment.h"
#include "VirtualPayment.h"

class Card : public VirtualPayment {
private:
    virtual int pay(double to_pay) override;

public:
    Card() : VirtualPayment("Card") {}

};


#endif
