cmake_minimum_required(VERSION 3.16)
project(CalcutorDemo C)

set(CMAKE_C_STANDARD 90)

add_executable(CalcutorDemo main.c core/calculator.h utils/io.h utils/io.c utils/floatstack.h utils/chardeque.h utils/floatstack.c core/calculator.c utils/chardeque.c type.h)