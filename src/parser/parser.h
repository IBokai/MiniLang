#ifndef PARSER_H
#define PARSER_H

#include "../AST/expressions.h"
#include "../AST/statements.h"
#include "../token/token.h"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)), position(0) {
        current_token = tokens_[0];
    }
    std::vector<std::unique_ptr<ASTNode>> parse();

private:
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseAssignment();
    std::unique_ptr<Statement> parseIfStatement();
    std::unique_ptr<Statement> parseWhileStatement();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseBinaryExpression(int minPrecedence);
    std::unique_ptr<Expression> parseUnaryExpression();
    std::unique_ptr<Expression> parsePrimaryExpression();
    Token peek() { return tokens_[position]; }
    void advance() { current_token = tokens_[++position]; }
    [[nodiscard]] bool isBinaryOP() const noexcept {
        return current_token.type == TokenType::LESS || current_token.type == TokenType::MORE ||
               current_token.type == TokenType::PLUS || current_token.type == TokenType::MINUS ||
               current_token.type == TokenType::MULTIPLY || current_token.type == TokenType::DIVIDE;
    }
    static int getPrecedence(Token const& token) {
        if (token.type == TokenType::LESS || token.type == TokenType::MORE) {
            return 1;
        }
        if (token.type == TokenType::PLUS || token.type == TokenType::MINUS) {
            return 2;
        }
        if (token.type == TokenType::MULTIPLY || token.type == TokenType::DIVIDE) {
            return 3;
        }
        throw std::runtime_error("Unexpected token in getPrecedence method");
    }
    Token current_token;
    std::vector<Token> tokens_;
    size_t position;
};
#endif
