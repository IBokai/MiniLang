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
    LPAREN,
    RPAREN,
    ENDFILE
};

class Token {
public:
    TokenType type_;
    std::string text_;
    std::pair<size_t, size_t> cordinates_;
    Token() = default;
    Token(TokenType const& type, std::string text, std::pair<size_t, size_t> cordinates) : type_(type), text_(std::move(text)), cordinates_(std::move(cordinates)){};
};

#endif