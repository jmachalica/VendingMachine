cmake_minimum_required(VERSION 3.17)
project(VendingMachine)

set(CMAKE_CXX_STANDARD 14)

add_executable(VendingMachine main.cpp VendingMachine.cpp VendingMachine.h Drink.cpp Drink.h Payment.h Card.cpp Card.h BLIK.cpp BLIK.h Cash.cpp Cash.h VirtualPayment.cpp VirtualPayment.h Container.h Errors.h)