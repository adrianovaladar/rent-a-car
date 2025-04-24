cmake_minimum_required(VERSION 3.26)
project(rent_a_car)

set(CMAKE_C_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

option(BUILD_COVERAGE "Enable coverage reporting" OFF)
if (BUILD_COVERAGE)
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
endif()

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
        src/logger.h
        src/logger.c
)

# Add tests - Only if BUILD_TESTS is enabled
option(BUILD_TESTS "Build tests" OFF)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
