
#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <stdexcept>

enum ALERT {
    CORRECT = 1,
    EXIT = -2,
    CANCEL = -3
};

struct Error : public std::exception {

    std::string error_message{nullptr};

    const char *what() const noexcept override {

        return error_message.c_str();

    }

    explicit Error(const std::string mess) : error_message{mess} {}


};


struct PaymentError : public Error {

    explicit PaymentError(const char *mess) : Error(std::string("Payment error: ") + mess) {


    };

};


struct CodeError : public PaymentError {


    explicit CodeError() : PaymentError("invalid code") {};

};


struct CriticalError : public Error {

    explicit CriticalError(const char *message) : Error(std::string("Critical Error: ") + message) {};

};


struct ContainerError : public Error {

    explicit ContainerError(const char *message) : Error(std::string("Container Error: ") + message) {};

};


#endif
