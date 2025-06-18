#include <gtest/gtest.h>

#include "../src/lexer/lexer.h"

TEST(LexerTest, basic) {
    std::string filename = "../samples/basic.mlang";
    Lexer l(filename);
    auto tokens = l.Tokenize();
    std::vector<Token> correct_tokens = {
            {TokenType::VAR, "a", {0, 0}},      {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "3", {0, 2}},      {TokenType::SEMICOL, ";", {0, 3}},
            {TokenType::VAR, "b", {1, 0}},      {TokenType::ASSIGNMENT, "=", {1, 1}},
            {TokenType::INT, "4", {1, 2}},      {TokenType::SEMICOL, ";", {1, 3}},
            {TokenType::VAR, "c", {2, 0}},      {TokenType::ASSIGNMENT, "=", {2, 1}},
            {TokenType::VAR, "a", {2, 2}},      {TokenType::PLUS, "+", {2, 3}},
            {TokenType::VAR, "b", {2, 4}},      {TokenType::SEMICOL, ";", {2, 5}},
            {TokenType::ENDFILE, "EOF", {3, 0}}};
    EXPECT_EQ(tokens.size(), correct_tokens.size());
    for (size_t i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(tokens[i].text_, correct_tokens[i].text_);
        EXPECT_EQ(tokens[i].type_, correct_tokens[i].type_);
        EXPECT_EQ(tokens[i].position_, correct_tokens[i].position_);
    }
}

TEST(LexerTest, factorial) {
    std::string filename = "../samples/factorial.mlang";
    Lexer l(filename);
    auto tokens = l.Tokenize();
    std::vector<Token> correct_tokens = {
            {TokenType::VAR, "res", {0, 0}},      {TokenType::ASSIGNMENT, "=", {0, 3}},
            {TokenType::INT, "1", {0, 4}},        {TokenType::SEMICOL, ";", {0, 5}},
            {TokenType::VAR, "n", {0, 7}},        {TokenType::ASSIGNMENT, "=", {0, 8}},
            {TokenType::INT, "6", {0, 9}},        {TokenType::SEMICOL, ";", {0, 10}},
            {TokenType::WHILE, "while", {1, 0}},  {TokenType::VAR, "n", {1, 6}},
            {TokenType::MORE, ">", {1, 7}},       {TokenType::INT, "1", {1, 8}},
            {TokenType::DO, "do", {1, 10}},       {TokenType::VAR, "res", {2, 4}},
            {TokenType::ASSIGNMENT, "=", {2, 7}}, {TokenType::VAR, "res", {2, 8}},
            {TokenType::MULTIPLY, "*", {2, 11}},  {TokenType::VAR, "n", {2, 12}},
            {TokenType::SEMICOL, ";", {2, 13}},   {TokenType::VAR, "n", {3, 4}},
            {TokenType::ASSIGNMENT, "=", {3, 5}}, {TokenType::VAR, "n", {3, 6}},
            {TokenType::MINUS, "-", {3, 7}},      {TokenType::INT, "1", {3, 8}},
            {TokenType::SEMICOL, ";", {3, 9}},    {TokenType::DONE, "done", {4, 0}},
            {TokenType::ENDFILE, "EOF", {5, 0}}};
    EXPECT_EQ(tokens.size(), correct_tokens.size());
    for (size_t i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(tokens[i].text_, correct_tokens[i].text_);
        EXPECT_EQ(tokens[i].type_, correct_tokens[i].type_);
        EXPECT_EQ(tokens[i].position_, correct_tokens[i].position_);
    }
}

TEST(LexerTest, fibonacci) {
    std::string filename = "../samples/fibonacci.mlang";
    Lexer l(filename);
    auto tokens = l.Tokenize();
    std::vector<Token> correct_tokens = {
            {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "0", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
            {TokenType::VAR, "b", {0, 5}},        {TokenType::ASSIGNMENT, "=", {0, 6}},
            {TokenType::INT, "1", {0, 7}},        {TokenType::SEMICOL, ";", {0, 8}},
            {TokenType::VAR, "n", {0, 10}},       {TokenType::ASSIGNMENT, "=", {0, 11}},
            {TokenType::INT, "5", {0, 12}},       {TokenType::SEMICOL, ";", {0, 13}},
            {TokenType::WHILE, "while", {1, 0}},  {TokenType::VAR, "n", {1, 6}},
            {TokenType::MORE, ">", {1, 7}},       {TokenType::INT, "1", {1, 8}},
            {TokenType::DO, "do", {1, 10}},       {TokenType::VAR, "b", {2, 4}},
            {TokenType::ASSIGNMENT, "=", {2, 5}}, {TokenType::VAR, "a", {2, 6}},
            {TokenType::PLUS, "+", {2, 7}},       {TokenType::VAR, "b", {2, 8}},
            {TokenType::SEMICOL, ";", {2, 9}},    {TokenType::VAR, "a", {3, 4}},
            {TokenType::ASSIGNMENT, "=", {3, 5}}, {TokenType::VAR, "b", {3, 6}},
            {TokenType::MINUS, "-", {3, 7}},      {TokenType::VAR, "a", {3, 8}},
            {TokenType::SEMICOL, ";", {3, 9}},    {TokenType::VAR, "n", {4, 4}},
            {TokenType::ASSIGNMENT, "=", {4, 5}}, {TokenType::VAR, "n", {4, 6}},
            {TokenType::MINUS, "-", {4, 7}},      {TokenType::INT, "1", {4, 8}},
            {TokenType::SEMICOL, ";", {4, 9}},    {TokenType::DONE, "done", {5, 0}},
            {TokenType::ENDFILE, "EOF", {6, 0}}};
    EXPECT_EQ(tokens.size(), correct_tokens.size());
    for (size_t i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(tokens[i].text_, correct_tokens[i].text_);
        EXPECT_EQ(tokens[i].type_, correct_tokens[i].type_);
        EXPECT_EQ(tokens[i].position_, correct_tokens[i].position_);
    }
}

TEST(LexerTest, unexpectedSymbol) {
    std::string filename = "../samples/lexerErrors/unexpected-symbol.mlang";
    Lexer l(filename);
    try {
        l.Tokenize();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Unexpected symbol");
    }
}

TEST(LexerTest, wrongNumber) {
    std::string filename = "../samples/lexerErrors/wrong-number.mlang";
    Lexer l(filename);
    try {
        l.Tokenize();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "error tokenizing NUMBER");
    }
}