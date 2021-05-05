
#include <iostream>
#include "Card.h"
#include <string>
#include "Errors.h"

extern int readEntered();

int Card::pay(double to_pay) {
    std::cout << "Payment: card" << std::endl << "To pay: " << to_pay << std::endl
              << "Insert card: enter 0" << std::endl << "Cancel payment - enter CANCEL" << std::endl
              << std::endl;

    int entered{};
    try { entered = readEntered(); }
    catch (Error &e) {
        std::cout << e.what();
        throw PaymentError("Card");
    }

    if (entered == CANCEL)return CANCEL;
    if (entered != 0)throw PaymentError("Card");

    if (to_pay >= 50) {
        std::cout << "Enter PIN code" << std::endl;
        std::string code;
        std::getline(std::cin, code);
        if (!validCode(code, 4)) {

            throw CodeError();

        }

    }
    int probability = rand() % 100 + 1;
    if (probability < 0)
        throw PaymentError(
                "Card");
    std::cout << "Payment was successful" << std::endl;
    return CORRECT;
}






