
#include "Cash.h"
#include <cmath>
#include "Errors.h"
#include <iostream>

extern int readEntered();

using namespace std;

int Cash::pay(double to_pay) {
    std::cout << "Payment: cash" << std::endl;
    double paid{0};
    while (true) {
        start:
        cout << "To pay: " << to_pay << std::endl;
        cout
                << "Enter coin: 10 cent, 20 cent,50 cent,1,2,5 (enter number)"
                << endl;
        cout << "Cancel payment - enter CANCEL" << endl;

        int entered{};
        try { entered = readEntered(); }
        catch (Error &e) {
            cout << e.what() << ", enter coin again " << endl;
            continue;
        }

        if (entered == CANCEL) {
            if (paid) {
                cout << "Change: " << paid << endl;
            }
            return CANCEL;
        }

        double coin = static_cast<double>(entered);

        for (int i = 0; i < values_num; i++) {
            if (coins[i] == coin) {
                if (coin >= 10)coin = coin / 100;
                if (!equalDouble(coin, to_pay)) {
                    if (coin > to_pay) {

                        cout << "Too big value, enter coin again" << endl;
                        goto start;
                    }
                }

                to_pay -= coin;
                paid += coin;
                if (equalDouble(to_pay, 0))return CORRECT;
                goto start;
            }
        }

        cout << "Invalid number" << endl;
    }


}

bool Cash::equalDouble(double a, double b) {
    double precision = 0.001;
    if (fabs(a - b) < precision)return true;
    return false;

}