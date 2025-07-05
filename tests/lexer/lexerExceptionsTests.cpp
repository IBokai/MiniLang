#include <gtest/gtest.h>

#include "../../src/lexer/lexer.h"
namespace tests::lexertests {
using namespace compiler::lexer;
TEST(LexerExceptionTest, unexpectedSymbol) {
    std::string filename = "../samples/lexerErrors/unexpected-symbol.mlang";
    Lexer l(filename);
    try {
        l.Tokenize();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Unexpected symbol");
    }
}

TEST(LexerExceptionTest, wrongNumber) {
    std::string filename = "../samples/lexerErrors/wrong-number.mlang";
    Lexer l(filename);
    try {
        l.Tokenize();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "error tokenizing NUMBER");
    }
}
}  // namespace tests::lexertests