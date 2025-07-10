#include <gtest/gtest.h>

#include "../../src/exceptions/exceptions.h"
#include "../../src/parser/parser.h"

namespace tests::parsertests {

using namespace compiler::parser;
using namespace compiler::exceptions;

TEST(ParserExceptionTest, noSemicolon) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "num", {0, 0}}, {TokenType::ASSIGNMENT, "=", {0, 4}},
        {TokenType::INT, "2", {0, 6}},   {TokenType::PLUS, "+", {0, 8}},
        {TokenType::INT, "2", {0, 10}},  {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Syntax error at (1 0): expected ';' after assignment, but got 'EOF'");
    }
}

TEST(ParserExceptionTest, notStatement) {
    std::vector<Token> tokens = {{TokenType::INT, "2", {0, 0}},
                                 {TokenType::PLUS, "+", {0, 1}},
                                 {TokenType::INT, "3", {0, 2}},
                                 {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Syntax error at (0 0): expected identifier, 'if', or 'while', but got '2'");
    }
}

TEST(ParserExceptionTest, noAssign) {
    std::vector<Token> tokens = {{TokenType::VAR, "a", {0, 0}},
                                 {TokenType::INT, "3", {0, 2}},
                                 {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Syntax error at (0 2): expected '=' after variable name, but got '3'");
    }
}

TEST(ParserExceptionTest, noThen) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},  {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "3", {0, 2}},  {TokenType::SEMICOL, ";", {0, 3}},
        {TokenType::IF, "if", {1, 0}},  {TokenType::VAR, "a", {1, 3}},
        {TokenType::LESS, "<", {1, 4}}, {TokenType::INT, "5", {1, 5}},
        {TokenType::VAR, "a", {2, 4}},  {TokenType::ASSIGNMENT, "=", {2, 5}},
        {TokenType::VAR, "a", {2, 6}},  {TokenType::MULTIPLY, "*", {2, 7}},
        {TokenType::INT, "2", {2, 8}},  {TokenType::SEMICOL, ";", {2, 9}},
        {TokenType::FI, "fi", {3, 0}},  {TokenType::ENDFILE, "EOF", {4, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Syntax error at (2 4): expected 'then' after condition in 'if' statement, but "
                  "got 'a'");
    }
}

TEST(ParserExceptionTest, noFi) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "3", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
        {TokenType::IF, "if", {1, 0}},        {TokenType::VAR, "a", {1, 3}},
        {TokenType::LESS, "<", {1, 4}},       {TokenType::INT, "5", {1, 5}},
        {TokenType::THEN, "then", {1, 7}},    {TokenType::VAR, "a", {2, 4}},
        {TokenType::ASSIGNMENT, "=", {2, 5}}, {TokenType::VAR, "a", {2, 6}},
        {TokenType::MULTIPLY, "*", {2, 7}},   {TokenType::INT, "2", {2, 8}},
        {TokenType::SEMICOL, ";", {2, 9}},    {TokenType::ENDFILE, "EOF", {3, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Syntax error at (3 0): expected 'fi' at end of 'if' statement, but got 'EOF'");
    }
}

TEST(ParserExceptionTest, noDo) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},       {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "3", {0, 2}},       {TokenType::SEMICOL, ";", {0, 3}},
        {TokenType::WHILE, "while", {1, 0}}, {TokenType::VAR, "a", {1, 6}},
        {TokenType::MORE, ">", {1, 7}},      {TokenType::INT, "0", {1, 8}},
        {TokenType::VAR, "a", {2, 4}},       {TokenType::ASSIGNMENT, "=", {2, 5}},
        {TokenType::VAR, "a", {2, 6}},       {TokenType::MINUS, "-", {2, 7}},
        {TokenType::INT, "1", {2, 8}},       {TokenType::SEMICOL, ";", {2, 9}},
        {TokenType::DONE, "done", {3, 0}},   {TokenType::ENDFILE, "EOF", {4, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Syntax error at (2 4): expected 'do' after condition in 'while' statement, but "
                  "got 'a'");
    }
}

TEST(ParserExceptionTest, noDone) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "3", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
        {TokenType::WHILE, "while", {1, 0}},  {TokenType::VAR, "a", {1, 6}},
        {TokenType::MORE, ">", {1, 7}},       {TokenType::INT, "0", {1, 8}},
        {TokenType::DO, "do", {1, 10}},       {TokenType::VAR, "a", {2, 4}},
        {TokenType::ASSIGNMENT, "=", {2, 5}}, {TokenType::VAR, "a", {2, 6}},
        {TokenType::MINUS, "-", {2, 7}},      {TokenType::INT, "1", {2, 8}},
        {TokenType::SEMICOL, ";", {2, 9}},    {TokenType::ENDFILE, "EOF", {3, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(
            std::string(e.what()),
            "Syntax error at (3 0): expected 'done' at end of 'while' statement, but got 'EOF'");
    }
}

TEST(ParserExceptionTest, unexpectedToken) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},       {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "2", {0, 2}},       {TokenType::PLUS, "+", {0, 3}},
        {TokenType::INT, "2", {0, 4}},       {TokenType::PLUS, "+", {0, 5}},
        {TokenType::WHILE, "while", {0, 6}}, {TokenType::SEMICOL, ";", {0, 11}},
        {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Syntax error at (0 6): expected number, variable, or '(', but got 'while'");
    }
}

TEST(ParserExceptionTest, noClosingParenthesis) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},     {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "2", {0, 2}},     {TokenType::MULTIPLY, "*", {0, 3}},
        {TokenType::LPAREN, "(", {0, 4}},  {TokenType::INT, "2", {0, 5}},
        {TokenType::PLUS, "+", {0, 6}},    {TokenType::INT, "2", {0, 7}},
        {TokenType::SEMICOL, ";", {0, 8}}, {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()), "Syntax error at (0 8): expected ')', but got ';'");
    }
}
}  // namespace tests::parsertests