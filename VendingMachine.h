
#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "Container.h"
#include "Drink.h"
#include "Payment.h"
#include "Card.h"

class VendingMachine {

private:

    Container<Payment *> payments{};
    Container<Drink *> drinks{};
    Container<int> drinks_quant{};

    size_t max_drinks_size{0};
    size_t max_quantity{0};
    double price_to_pay{0};

    bool isAnyDrink() const;

    inline void setPricetoPay(int drink_id) {
        try {
            this->price_to_pay = drinks[drink_id]->price;
        } catch (ContainerError &e) {
            std::cout << e.what() << std::endl;
            throw Error("Price can't be set");
        }
    }

    inline void resetPricetoPay() {
        this->price_to_pay = 0;
    }

    bool isValidDrinkId(int) const;

    inline void decquantity(int drink_id) {
        try {
            drinks_quant[drink_id]--;
        } catch (ContainerError &e) {
            std::cout << e.what() << std::endl;
            throw CriticalError("Quantity can't be decreased");
        }
    }

    inline const char *getDrinkName(int drink_id) const {
        try {
            return drinks[drink_id]->name;
        }
        catch (ContainerError &e) {
            std::cout << e.what() << std::endl;
            throw CriticalError("Product name can't be accessed");
        }

    }


    int choosePaymentMethod() const;

    bool isValidPayment(int) const;

    int chooseDrink() const;

    void print() const;


public:
    explicit VendingMachine(size_t max_drinks_size = 0, size_t max_quantity = 0);

    ~VendingMachine();

    void run();

    void AddDrink(Drink *drink, int quantity);

    void addPaymentMethod(Payment *payment);

    VendingMachine(const VendingMachine &) = delete;

    VendingMachine &operator=(const VendingMachine &) = delete;

};


#endif
