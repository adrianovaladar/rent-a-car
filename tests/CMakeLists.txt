set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 17)
add_executable(AllTests main.cpp
        ../src/input.h
        ../src/input.c
        ../src/date.h
        ../src/date.c
        InputTests.cpp
        InputTests.h)
target_compile_definitions(AllTests PRIVATE TEST=1)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(AllTests gtest gtest_main gmock_main)
