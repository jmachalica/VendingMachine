
#include "VendingMachine.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int readEntered();

void VendingMachine::run() {
    if (!payments.size()) {
        throw CriticalError("No payment method available");
    }
    while (isAnyDrink()) {
        print:
        this->print();

        int drink_id = chooseDrink();
        if (drink_id == EXIT) {
            cout << "EXIT, vending machine is going to turn off.";
            return;
        }

        const char *name{};
        try { name = getDrinkName(drink_id); }
        catch (CriticalError &e) {
            throw;
        }
        cout << "Chosen drink: " << name << endl;


        try {
            setPricetoPay(drink_id);
        }
        catch (Error &e) {
            throw CriticalError(e.what());
        }

        while (true) {
            choosepayment:

            int chosen_payment{};
            try {
                chosen_payment = choosePaymentMethod();
            }
            catch (CriticalError &) {
                throw;
            }
            //payment
            int payment_result{0};
            try {
                payment_result = payments[chosen_payment]->pay(this->price_to_pay);
            }
            catch (CodeError &e) {
                cout << e.what() << ",choose payment method again" << endl;
                continue;
            }
            catch (PaymentError &e) {
                cout << e.what() << ", try payment again" << endl;
                continue;
            }

            if (payment_result == CANCEL) {
                cout << "Payment was cancelled" << endl << "Cancel your order - enter 0" << endl
                     << "Choose payment method again - enter 1" << endl << endl;

                while (true) {
                    int decision{};
                    try {
                        decision = readEntered();
                    }
                    catch (Error &e) {
                        cout << e.what() << ", try to enter your decision again" << endl;
                        continue;
                    }
                    if (decision == 0) {
                        cout << "Order was cancelled" << endl;
                        resetPricetoPay();
                        goto print;
                    }
                    if (decision == 1)goto choosepayment;

                    cout << "Enter a valid number" << endl;
                    continue;

                }
            }

            //payment successful
            break;

        }
        cout << endl << "Thank you for shopping" << endl << endl;
//decrement product quantity
        try {
            decquantity(drink_id);
            resetPricetoPay();
        }

        catch (Error &e) {
            cout << e.what() << endl;
            try {
                delete drinks.del(drink_id);
            }
            catch (ContainerError &er) {
                cout << er.what() << endl;
                throw CriticalError("drink can't be deleted");

            }
            try { drinks_quant.del(drink_id); }
            catch (ContainerError &e) {
                cout << e.what() << endl;
                throw CriticalError("quantity can't be deleted");

            }


        }
    }

}


VendingMachine::~VendingMachine() {

    for (int i = 0; i < drinks.size(); i++) {
        delete drinks[i];
    }
    for (int i = 0; i < payments.size(); i++) {
        delete payments[i];
    }


}

void VendingMachine::print() const {

    cout << endl << "Available products:" << endl << endl;
    int drinks_size = drinks.size();
    for (int i = 0; i < drinks_size; i++) {
        cout << drinks[i] << "  |  quantity: " << drinks_quant[i] << endl;
    }
}

int VendingMachine::chooseDrink() const {

    size_t drinks_size = drinks.size();
    if (drinks_size > 1) {
        cout << "Choose drink: enter number 0-" << drinks_size - 1;
    } else cout << "Choose drink: enter number 0";

    cout << "  | enter EXIT to end" << endl
         << endl;
    int drink_id;

    while (true) {
        //user decision
        try {
            drink_id = readEntered();
        }
        catch (Error &e) {
            cout << e.what() << endl << "Invalid product number" << endl;
            cout << "Choose different product" << endl;
            continue;

        }
        if (drink_id == EXIT) {
            return EXIT;
        }

        if (!isValidDrinkId(drink_id)) {
            cout << "Choose different product" << endl;
            continue;
        }

        break;

    }

    return drink_id;


}


bool VendingMachine::isAnyDrink() const {
    for (int i = 0; i < drinks.size(); i++) {
        if (drinks_quant[i])return true;

    }
    cout << "Vending machine is empty. Thanks for shopping" << endl;
    return false;
}

bool VendingMachine::isValidDrinkId(int drink_id) const {

    if (drink_id < 0 || drink_id > (drinks.size() - 1)) {
        cout << "Invalid product index" << endl;
        return false;

    }
    if (drinks_quant[drink_id])return true;

    cout << "This product is no longer available " << endl;
    return false;
}


int readEntered() {
    std::string line;
    std::getline(std::cin, line);
    if (line == "EXIT")return EXIT;
    if (line == "CANCEL")return CANCEL;

    try {
        int i = std::stoi(line);
        return i;
    }
    catch (std::exception const &e) {

        throw Error("Reading error");
    }

}


void VendingMachine::AddDrink(Drink *drink, int quantity) {

    if (!drink) {
        cout << "Invalid product, product can't be added" << endl;
        return;
    }
    if (drinks.size() >= max_drinks_size) {
        cout << "Vending machine is full, product can't be added: " << drink << endl;
        delete drink;
        return;

    }
    if (drink->price <= 0) {
        cout << "Invalid price, product can't be added: " << drink << endl;
        delete drink;
        return;
    }
    if (quantity < 0 || quantity > max_quantity) {
        cout << "Invalid quantity, product can't be added: " << drink << endl;
        delete drink;
        return;
    }
    try { drinks.add(drink); }
    catch (ContainerError &e) {

        cout << e.what() << "Product can't be added" << endl;
        return;

    }
    try { drinks_quant.add(quantity); }
    catch (ContainerError &e) {
        cout << e.what() << "Quantity can't be added, the product will be deleted" << endl;
        delete drinks.remove();
        return;

    }


}

VendingMachine::VendingMachine(size_t max_drinks_size, size_t max_quantity) : max_drinks_size{max_drinks_size},
                                                                              max_quantity{max_quantity} {
    //drinks = new Drink *[max_drinks_size]{};
//    drinks_quant = new int[max_drinks_size]{};

}

int VendingMachine::choosePaymentMethod() const {
    int payments_size = payments.size();

    if (payments_size > 1) { cout << "Choose payment method" << ", enter number 0-" << payments_size - 1 << endl; }
    else {
        cout << "Available payment: ";
        try {
            cout << payments[0]->payment_name << endl;
        }
        catch (ContainerError &e) {
            cout << e.what();
            throw CriticalError("Available payment methods can't be accessed");
        }
        return 0;
    }

    cout << "Available payment methods:" << endl;

    for (int i = 0; i < payments_size; i++) {
        try {
            cout << i << ". " << payments[i]->payment_name << endl;
        }
        catch (ContainerError &e) {
            cout << e.what();
            throw CriticalError("Payment method can't be accessed");
        }
    }
    cout << endl;

    int chosenPayment{0};
    while (true) {
        try {
            chosenPayment = readEntered();
            if (!isValidPayment(chosenPayment)) {
                cout << "Choose another payment method" << endl;
                continue;
            }
        }
        catch (Error &e) {
            cout << "Enter payment number again" << endl;
            continue;
        }

        break;

    }


    return chosenPayment;


}

bool VendingMachine::isValidPayment(int num) const {

    return (num >= 0 && num < payments.size());

}

void VendingMachine::addPaymentMethod(Payment *payment) {
    if (!payment || !payment->payment_name) {
        cout << "Invalid payment number, this payment method can't be added" << endl;
        return;
    }

    try {
        this->payments.add(payment);
    }
    catch (ContainerError &e) {
        cout << e.what() << ", payment: " << payment->payment_name << " wasn't added" << endl;

        return;


    }


}

