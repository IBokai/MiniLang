#ifndef TOKEN_H
#define TOKEN_H

#include <string>
namespace compiler::lexer {
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
    ENDFILE,
    DEFAULT
};

class Token {
public:
    TokenType type_;
    std::string text_;
    std::pair<size_t, size_t> position_;
    Token() : type_(TokenType::DEFAULT), text_(""), position_(0, 0){};
    Token(TokenType const& type, std::string text, std::pair<size_t, size_t> cordinates)
        : type_(type), text_(std::move(text)), position_(std::move(cordinates)){};
};
}  // namespace compiler::lexer
#endif