#include <iostream>
#include <ctime>
#include <fstream>
#include "VendingMachine.h"
#include "Drink.h"
#include "Payment.h"
#include "BLIK.h"
#include "Card.h"
#include "Cash.h"

int main(int argc, char *argv[]) {

    std::ofstream file;
    if (argc == 2) {
        file.open(argv[1]);

        if (file.is_open()) {
            std::cin.rdbuf(file.rdbuf());
        }
    }


    srand(time(0));
    try {
        VendingMachine automat{4, 10};
        automat.addPaymentMethod(new Cash);
        automat.addPaymentMethod(new Card);
        automat.addPaymentMethod(new BLIK);


        automat.AddDrink(new Drink{"Water 0,5l", 2}, 3);
        automat.AddDrink(new Drink{"Coca-Cola 1l", 3.7}, 3);
        automat.AddDrink(new Drink{"Pepsi 250 ml", 6.1}, 3);
        automat.AddDrink(new Drink{"Orange juice 1l", 10}, 3);
        automat.run();
    }
    catch (CriticalError &e) {
        std::cout << e.what() << ", vending machine is going to turn off." << std::endl;
        if (file.is_open()) {
            file.close();
        }
        return 1;
    }


    if (file.is_open()) {
        file.close();
    }

    return 0;
}
