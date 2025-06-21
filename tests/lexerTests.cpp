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
    ASSERT_EQ(tokens.size(), correct_tokens.size());
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
    ASSERT_EQ(tokens.size(), correct_tokens.size());
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
    ASSERT_EQ(tokens.size(), correct_tokens.size());
    for (size_t i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(tokens[i].text_, correct_tokens[i].text_);
        EXPECT_EQ(tokens[i].type_, correct_tokens[i].type_);
        EXPECT_EQ(tokens[i].position_, correct_tokens[i].position_);
    }
}

TEST(LexerTest, arithmeticExpression) {
    std::string filename = "../samples/arithmetic-expression.mlang";
    Lexer l(filename);
    auto tokens = l.Tokenize();
    std::vector<Token> correct_tokens = {
            {TokenType::VAR, "expression", {0, 0}}, {TokenType::ASSIGNMENT, "=", {0, 11}},
            {TokenType::LPAREN, "(", {0, 13}},      {TokenType::INT, "5", {0, 14}},
            {TokenType::PLUS, "+", {0, 16}},        {TokenType::INT, "3", {0, 18}},
            {TokenType::MULTIPLY, "*", {0, 20}},    {TokenType::MINUS, "-", {0, 22}},
            {TokenType::INT, "2", {0, 23}},         {TokenType::RPAREN, ")", {0, 24}},
            {TokenType::DIVIDE, "/", {0, 26}},      {TokenType::LPAREN, "(", {0, 28}},
            {TokenType::INT, "4", {0, 29}},         {TokenType::MINUS, "-", {0, 31}},
            {TokenType::INT, "1", {0, 33}},         {TokenType::RPAREN, ")", {0, 34}},
            {TokenType::SEMICOL, ";", {0, 35}},     {TokenType::ENDFILE, "EOF", {1, 0}}};
    ASSERT_EQ(tokens.size(), correct_tokens.size());
    for (size_t i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(tokens[i].text_, correct_tokens[i].text_);
        EXPECT_EQ(tokens[i].type_, correct_tokens[i].type_);
        EXPECT_EQ(tokens[i].position_, correct_tokens[i].position_);
    }
}

TEST(LexerTest, nestedIf) {
    std::string filename = "../samples/nested-if.mlang";
    Lexer l(filename);
    auto tokens = l.Tokenize();
    std::vector<Token> correct_tokens = {
            {TokenType::VAR, "n", {0, 0}},      {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "10", {0, 2}},     {TokenType::SEMICOL, ";", {0, 4}},
            {TokenType::VAR, "flag", {1, 0}},   {TokenType::ASSIGNMENT, "=", {1, 4}},
            {TokenType::INT, "0", {1, 5}},      {TokenType::SEMICOL, ";", {1, 6}},
            {TokenType::IF, "if", {2, 0}},      {TokenType::VAR, "n", {2, 3}},
            {TokenType::MORE, ">", {2, 4}},     {TokenType::INT, "5", {2, 5}},
            {TokenType::THEN, "then", {2, 7}},  {TokenType::IF, "if", {3, 4}},
            {TokenType::VAR, "n", {3, 7}},      {TokenType::LESS, "<", {3, 8}},
            {TokenType::INT, "15", {3, 9}},     {TokenType::THEN, "then", {3, 12}},
            {TokenType::VAR, "flag", {4, 8}},   {TokenType::ASSIGNMENT, "=", {4, 12}},
            {TokenType::INT, "1", {4, 13}},     {TokenType::SEMICOL, ";", {4, 14}},
            {TokenType::FI, "fi", {5, 4}},      {TokenType::FI, "fi", {6, 0}},
            {TokenType::ENDFILE, "EOF", {7, 0}}};
    EXPECT_EQ(tokens.size(), correct_tokens.size());
    for (size_t i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(tokens[i].text_, correct_tokens[i].text_);
        EXPECT_EQ(tokens[i].type_, correct_tokens[i].type_);
        EXPECT_EQ(tokens[i].position_, correct_tokens[i].position_);
    }
}

TEST(LexerTest, nestedWhile) {
    std::string filename = "../samples/nested-while.mlang";
    Lexer l(filename);
    auto tokens = l.Tokenize();
    std::vector<Token> correct_tokens = {
            {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "0", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
            {TokenType::VAR, "b", {1, 0}},        {TokenType::ASSIGNMENT, "=", {1, 1}},
            {TokenType::INT, "0", {1, 2}},        {TokenType::SEMICOL, ";", {1, 3}},
            {TokenType::WHILE, "while", {2, 0}},  {TokenType::VAR, "a", {2, 6}},
            {TokenType::LESS, "<", {2, 7}},       {TokenType::INT, "2", {2, 8}},
            {TokenType::DO, "do", {2, 10}},       {TokenType::VAR, "c", {3, 4}},
            {TokenType::ASSIGNMENT, "=", {3, 5}}, {TokenType::INT, "0", {3, 6}},
            {TokenType::SEMICOL, ";", {3, 7}},    {TokenType::WHILE, "while", {4, 4}},
            {TokenType::VAR, "c", {4, 10}},       {TokenType::LESS, "<", {4, 11}},
            {TokenType::INT, "3", {4, 12}},       {TokenType::DO, "do", {4, 14}},
            {TokenType::VAR, "c", {5, 8}},        {TokenType::ASSIGNMENT, "=", {5, 9}},
            {TokenType::VAR, "c", {5, 10}},       {TokenType::PLUS, "+", {5, 11}},
            {TokenType::INT, "1", {5, 12}},       {TokenType::SEMICOL, ";", {5, 13}},
            {TokenType::VAR, "b", {6, 8}},        {TokenType::ASSIGNMENT, "=", {6, 9}},
            {TokenType::VAR, "b", {6, 10}},       {TokenType::PLUS, "+", {6, 11}},
            {TokenType::INT, "1", {6, 12}},       {TokenType::SEMICOL, ";", {6, 13}},
            {TokenType::DONE, "done", {7, 4}},    {TokenType::VAR, "a", {8, 4}},
            {TokenType::ASSIGNMENT, "=", {8, 5}}, {TokenType::VAR, "a", {8, 6}},
            {TokenType::PLUS, "+", {8, 7}},       {TokenType::INT, "1", {8, 8}},
            {TokenType::SEMICOL, ";", {8, 9}},    {TokenType::DONE, "done", {9, 0}},
            {TokenType::ENDFILE, "EOF", {10, 0}}};
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