//
// Created by hp on 2020-12-11.
//

#ifndef BLIK_H
#define BLIK_H

#include "Payment.h"
#include <iostream>
#include "VirtualPayment.h"

class BLIK : public VirtualPayment {
private:
    virtual int pay(double to_pay) override;

public:

    BLIK() : VirtualPayment("BLIK") {}

};


#endif
