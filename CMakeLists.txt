cmake_minimum_required(VERSION 3.23)
project(rent_a_car C)

set(CMAKE_C_STANDARD 17)

add_executable(rent_a_car
        src/main.c src/input.c src/input.h src/date.c src/date.h src/constants.h src/vehicle.c src/vehicle.h src/contract.c src/contract.h src/customer.c src/customer.h)
