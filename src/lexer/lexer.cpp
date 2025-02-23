#include "lexer.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<std::string, TokenType> keywordTypes{{"if", TokenType::IF},
                                                        {"fi", TokenType::FI},
                                                        {"then", TokenType::THEN},
                                                        {"while", TokenType::WHILE},
                                                        {"do", TokenType::DO},
                                                        {"done", TokenType::DONE}};

std::unordered_map<std::string, TokenType> operatorTypes{
        {"=", TokenType::ASSIGNMENT}, {"+", TokenType::PLUS},     {"-", TokenType::MINUS},
        {"/", TokenType::DIVIDE},     {"*", TokenType::MULTIPLY}, {"<", TokenType::LESS},
        {">", TokenType::MORE},       {"(", TokenType::RPAREN},   {")", TokenType::LPAREN}};

std::vector<Token> Lexer::Tokenize() {
    std::vector<Token> result;
    std::unordered_set<char> operators = {'=', '+', '-', '/', '*', '<', '>', '(', ')'};
    while (position != text.length()) {
        if (isspace(text[position])) {
            position++;
        }
        if (isalpha(text[position])) {
            result.push_back(TokenizeVarOrKeyword());
        }
        if (isdigit(text[position])) {
            result.push_back(TokenizeNumber());
        }
        if (text[position] == ';') {
            result.push_back(TokenizeSemicol());
        } 
        if (operators.count(text[position])){
            result.push_back(TokenizeOperator());
        }
    };
    return result;
}

Token Lexer::TokenizeNumber() {
    std::string tokenText;
    while (isdigit(text[position])) {
        tokenText += text[position];
        position++;
    }
    if (!isalpha(text[position])) {
        return Token(TokenType::INT, tokenText);
    }
    throw std::runtime_error("error tokenizing NUMBER");
}

Token Lexer::TokenizeVarOrKeyword() {
    std::string tokenText;
    std::unordered_set<std::string> keywords = {"if", "fi", "then", "while", "do" , "done"};
    while (isalpha(text[position]) || isdigit(text[position])) {
        tokenText += text[position];
        position++;
    }
    if (keywords.count(tokenText)) {
        if (!isalpha(text[position] && !isdigit(text[position]))) {
            return Token(keywordTypes.at(tokenText), tokenText);
        }
        else{
            std::cout << tokenText;
            throw std::runtime_error("error tokenizing VAR or KEYWORD");
        }
    }
    return Token(TokenType::VAR, tokenText);
}

Token Lexer::TokenizeSemicol() {
    position++;
    return Token(TokenType::SEMICOL, ";");
}

Token Lexer::TokenizeOperator() {
    std::string tokenText;
    tokenText += text[position];
    position++;
    return Token(operatorTypes.at(tokenText), tokenText);
}

Lexer::Lexer(std::string filename) {
    std::ifstream file(filename);
    std::string temp;
    while (std::getline(file, temp)) {
        text += temp;
    }
    position = 0;
}
