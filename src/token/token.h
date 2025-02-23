#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    INT,
    VAR,
    ASSIGNMENT,
    IF,
    FI,
    THEN,
    WHILE,
    DO,
    DONE,
    LESS,
    MORE,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    SEMICOL,
    RPAREN,
    LPAREN
};

class Token {
public:
    TokenType type;
    std::string text;
    Token(TokenType type, std::string text) : type(type), text(text){};
};

#endif