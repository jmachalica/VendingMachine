//
// Created by hp on 2020-12-11.
//
#include "Errors.h"

#include "BLIK.h"
#include <iostream>
#include <string>


int BLIK::pay(double to_pay) {

    std::cout << "Payment: BLIK" << std::endl << "To pay: " << to_pay << std::endl
              << "Enter BLIK code: " << std::endl << "Cancel payment : enter CANCEL" << std::endl
              << std::endl;

    std::string code;
    std::getline(std::cin, code);
    if (code == "CANCEL")return CANCEL;
    if (!validCode(code, 6)) {

        throw CodeError();
    }
    int probability = rand() % 100 + 1;
    if (probability > 0)
        throw PaymentError(
                "BLIK");
    std::cout << "Payment was successful" << std::endl;

    return CORRECT;


}



