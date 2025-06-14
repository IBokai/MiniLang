#include "lexer.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<std::string, TokenType> keywordTypes{
        {"if", TokenType::IF},       {"fi", TokenType::FI}, {"then", TokenType::THEN},
        {"while", TokenType::WHILE}, {"do", TokenType::DO}, {"done", TokenType::DONE}};

std::unordered_map<std::string, TokenType> operatorTypes{
        {"=", TokenType::ASSIGNMENT}, {"+", TokenType::PLUS},     {"-", TokenType::MINUS},
        {"/", TokenType::DIVIDE},     {"*", TokenType::MULTIPLY}, {"<", TokenType::LESS},
        {">", TokenType::MORE},       {"(", TokenType::LPAREN},   {")", TokenType::RPAREN}};

std::vector<Token> Lexer::Tokenize() {
    std::vector<Token> result;
    std::unordered_set<char> operators = {'=', '+', '-', '/', '*', '<', '>', '(', ')'};
    while (std::getline(file, line)) {
        position = 0;
        while (position != line.length()) {
            if (isspace(line[position])) {
                position++;
            }
            if (isalpha(line[position])) {
                result.push_back(TokenizeVarOrKeyword());
            }
            if (isdigit(line[position])) {
                result.push_back(TokenizeNumber());
            }
            if (line[position] == ';') {
                result.push_back(TokenizeSemicolon());
            }
            if (operators.count(line[position])) {
                result.push_back(TokenizeOperator());
            }
        }
    }
    file.close();
    result.push_back(Token(TokenType::ENDFILE, "EOF"));
    return result;
}

Token Lexer::TokenizeNumber() {
    std::string tokenText;
    while (isdigit(line[position])) {
        tokenText += line[position];
        position++;
    }
    if (!isalpha(line[position])) {
        return Token(TokenType::INT, tokenText);
    }
    throw std::runtime_error("error tokenizing NUMBER");
}

Token Lexer::TokenizeVarOrKeyword() {
    std::string tokenText;
    std::unordered_set<std::string> keywords = {"if", "fi", "then", "while", "do", "done"};
    while (isalpha(line[position]) || isdigit(line[position])) {
        tokenText += line[position];
        position++;
    }
    if (keywords.count(tokenText)) {
        if (!isalpha(line[position] && !isdigit(line[position]))) {
            return Token(keywordTypes.at(tokenText), tokenText);
        } else {
            std::cout << tokenText;
            throw std::runtime_error("error tokenizing VAR or KEYWORD");
        }
    }
    return {TokenType::VAR, tokenText};
}

Token Lexer::TokenizeSemicolon() {
    position++;
    return {TokenType::SEMICOL, ";"};
}

Token Lexer::TokenizeOperator() {
    std::string tokenText;
    tokenText += line[position];
    position++;
    return {operatorTypes.at(tokenText), tokenText};
}

Lexer::Lexer(std::string const& filename) {
    file.open(filename);
    if (!file) {
        throw std::runtime_error("Error, while processing file");
    }
    position = 0;
}