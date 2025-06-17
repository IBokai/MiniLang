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
        while (position != line.length()) {
            if (isspace(line[position])) {
                position++;
                if (position >= line.size()) {
                    break;
                }
            } else if (isalpha(line[position])) {
                result.push_back(TokenizeVarOrKeyword());
                if (position >= line.size()) {
                    break;
                }
            } else if (isdigit(line[position])) {
                result.push_back(TokenizeNumber());
                if (position >= line.size()) {
                    break;
                }
            } else if (line[position] == ';') {
                result.push_back(TokenizeSemicolon());
                if (position >= line.size()) {
                    break;
                }
            } else if (operators.count(line[position])) {
                result.push_back(TokenizeOperator());
                if (position >= line.size()) {
                    break;
                }
            } else {
                throw std::runtime_error("Unexpected symbol");
            }
        }
        position = 0;
        line_index++;
    }
    file.close();
    result.push_back(Token(TokenType::ENDFILE, "EOF", {line_index, position}));
    return result;
}

Token Lexer::TokenizeNumber() {
    std::string tokenText;
    size_t starting_posistion = position;
    while (isdigit(line[position])) {
        tokenText += line[position];
        position++;
    }
    if (!isalpha(line[position])) {
        return {TokenType::INT, tokenText, {line_index, starting_posistion}};
    }
    throw std::runtime_error("error tokenizing NUMBER");
}

Token Lexer::TokenizeVarOrKeyword() {
    std::string tokenText;
    size_t starting_position = position;
    std::unordered_set<std::string> keywords = {"if", "fi", "then", "while", "do", "done"};
    while (isalpha(line[position]) || isdigit(line[position])) {
        tokenText += line[position];
        position++;
    }
    if (keywords.count(tokenText)) {
        if (!isalpha(line[position] && !isdigit(line[position]))) {
            return {keywordTypes.at(tokenText), tokenText, {line_index, starting_position}};
        } else {
            throw std::runtime_error("error tokenizing VAR or KEYWORD");
        }
    }
    return {TokenType::VAR, tokenText, {line_index, starting_position}};
}

Token Lexer::TokenizeSemicolon() {
    size_t starting_position = position;
    position++;
    return {TokenType::SEMICOL, ";", {line_index, starting_position}};
}

Token Lexer::TokenizeOperator() {
    std::string tokenText;
    size_t starting_position = position;
    tokenText += line[position];
    position++;
    return {operatorTypes.at(tokenText), tokenText, {line_index, starting_position}};
}

Lexer::Lexer(std::string const& filename) {
    file.open(filename);
    if (!file) {
        throw std::runtime_error("Error, while processing file");
    }
    position = 0;
    line_index = 0;
}