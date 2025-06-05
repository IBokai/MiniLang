cmake_minimum_required(VERSION 3.28.3)

include_directories(.)

project(main)
set(CMAKE_CXX_STANDARD 17) 

add_compile_options(-O3 -Wall -Wextra -Wpedantic -Werror)

add_executable(main
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/parser/expressionParser.cpp
)