

#ifndef PAYMENT_H
#define PAYMENT_H


class Payment {
protected:
    const char *payment_name{};

    virtual int pay(double to_pay) = 0;

    friend class VendingMachine;

    explicit Payment(const char *name) : payment_name{name} {}

};


#endif
