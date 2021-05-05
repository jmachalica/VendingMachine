
#ifndef CASH_H
#define CASH_H

#include "Payment.h"

class Cash : public Payment {
private:
    constexpr static int values_num{6};
    const double coins[values_num]{10, 20, 50, 1, 2, 5};

    bool equalDouble(double a, double b);

    virtual int pay(double to_pay) override;

public:
    Cash() : Payment("Cash") {}
};

#endif
