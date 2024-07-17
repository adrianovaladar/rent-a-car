cmake_minimum_required(VERSION 3.26)
project(rent_a_car)

set(CMAKE_C_STANDARD 17)
add_compile_options(--coverage)
add_link_options(--coverage)

add_executable(rent_a_car
        src/main.c
        src/input.c
        src/input.h
        src/date.c
        src/date.h
        src/constants.h
        src/vehicle.c
        src/vehicle.h
        src/contract.c
        src/contract.h
        src/customer.c
        src/customer.h
        src/application.h
        src/application.c
)

# Add tests
add_subdirectory(tests)
