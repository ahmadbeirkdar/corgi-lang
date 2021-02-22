cmake_minimum_required(VERSION 3.17)
project(corgi-lang)

set(CMAKE_CXX_STANDARD 20)

add_executable(corgi-lang main.cpp token.h lexer.cpp lexer.h)