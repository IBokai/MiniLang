#include <gtest/gtest.h>

#include "../../src/parser/parser.h"

TEST(ParserExceptionTest, noSemicolon) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "num", {0, 0}}, {TokenType::ASSIGNMENT, "=", {0, 4}},
        {TokenType::INT, "2", {0, 6}},   {TokenType::PLUS, "+", {0, 8}},
        {TokenType::INT, "2", {0, 10}},  {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected semicolon after assignment statement");
    }
}

TEST(ParserExceptionTest, noStatement) {
    std::vector<Token> tokens = {{TokenType::INT, "2", {0, 0}},
                                 {TokenType::PLUS, "+", {0, 1}},
                                 {TokenType::INT, "3", {0, 2}},
                                 {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.Parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected statement");
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
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected assignment sign after variable name");
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
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Expected then keyword after condition expression in if statement");
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
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected fi keyword before the end of the program");
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
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Expected do keyword after condition epxression in while statement");
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
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected done keyword before the end of the program");
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
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected number, variable or '('");
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
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected ')'");
    }
}