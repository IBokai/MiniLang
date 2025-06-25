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

    void advance() { current_token = tokens_[++position]; }

    [[nodiscard]] bool isBinaryOP() const noexcept {
        return current_token.type_ == TokenType::LESS || current_token.type_ == TokenType::MORE ||
               current_token.type_ == TokenType::PLUS || current_token.type_ == TokenType::MINUS ||
               current_token.type_ == TokenType::MULTIPLY ||
               current_token.type_ == TokenType::DIVIDE;
    }

    static int getPrecedence(Token const& token) {
        if (token.type_ == TokenType::LESS || token.type_ == TokenType::MORE) {
            return 1;
        }
        if (token.type_ == TokenType::PLUS || token.type_ == TokenType::MINUS) {
            return 2;
        }
        if (token.type_ == TokenType::MULTIPLY || token.type_ == TokenType::DIVIDE) {
            return 3;
        }
        throw std::runtime_error("Unexpected token in getPrecedence method");
    }

    Token current_token;
    std::vector<Token> tokens_;
    size_t position;
};
#endif
