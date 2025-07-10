#include <gtest/gtest.h>

#include "../../src/exceptions/exceptions.h"
#include "../../src/lexer/lexer.h"

namespace tests::lexertests {

using namespace compiler::lexer;
using namespace compiler::exceptions;

TEST(LexerExceptionTest, unexpectedSymbol) {
    std::string filename = "../samples/lexerErrors/unexpected-symbol.mlang";
    Lexer l(filename);
    try {
        l.Tokenize();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()), "Lexical error at (0 6): unexpected symbol: '@'");
    }
}

TEST(LexerExceptionTest, wrongNumber) {
    std::string filename = "../samples/lexerErrors/wrong-number.mlang";
    Lexer l(filename);
    try {
        l.Tokenize();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()), "Lexical error at (0 10): invalid number");
    }
}
}  // namespace tests::lexertests