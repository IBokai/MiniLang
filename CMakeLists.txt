cmake_minimum_required(VERSION 3.28.3)

project(compiler)
set(CMAKE_CXX_STANDARD 17) 

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_compile_options(-O3 -Wall -Wextra -Wpedantic -Werror)

add_executable(compiler
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/parser/expressionParser.cpp
    src/parser/statementParser.cpp
)

add_executable(tests
    tests/lexer/lexerTests.cpp
    tests/lexer/lexerExceptionsTests.cpp
    tests/parser/parserTests.cpp
    tests/parser/parserExceptionsTests.cpp
    tests/code-generator/C/CcodegeneratorTests.cpp
    tests/code-generator/risc/riscCodegeneratorTests.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/parser/expressionParser.cpp
    src/parser/statementParser.cpp
)

target_link_libraries(tests
  PRIVATE
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)