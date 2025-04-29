#pragma once
#include "../AST/ASTNode.h"
#include "../token/token.h"

class Parser {
public:
    Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)), position(0) {}
    std::vector<std::unique_ptr<ASTNode>> parse();

private:
    std::unique_ptr<ASTNode> parseAssignemt();
    std::unique_ptr<ASTNode> parseIfStatement();
    std::unique_ptr<ASTNode> parseWhileStatement();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseBinaryExpression();
    std::unique_ptr<Expression> parseUnaryExpression();
    Token consume() { return tokens_[position++]; }
    Token peek() { return tokens_[position]; }
    void advance() { ++position; }
    Token current_token;
    size_t position;
    std::vector<Token> tokens_;
};