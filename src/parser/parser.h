#pragma once
#include "../AST/ASTNode.h"
#include "../token/token.h"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)), position(0) {}
    std::vector<std::unique_ptr<ASTNode>> parse();

private:
    std::unique_ptr<ASTNode> parseAssignemt();
    std::unique_ptr<ASTNode> parseIfStatement();
    std::unique_ptr<ASTNode> parseWhileStatement();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseBinaryExpression();
    std::unique_ptr<Expression> parseUnaryExpression();
    Token peek() { return tokens_[position]; }
    Token advance() { return tokens_[position++]; }
    bool match(TokenType const& type) {
        if (tokens_[position].type == type) {
            position++;
            return true;
        }
        return false;
    }
    Token current_token;
    std::vector<Token> tokens_;
    size_t position;
};