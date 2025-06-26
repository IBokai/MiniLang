#ifndef PARSER_H
#define PARSER_H

#include "../AST/expressions.h"
#include "../AST/statements.h"
#include "../token/token.h"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)), position_(0) {
        current_token_ = tokens_[0];
    }
    std::vector<std::unique_ptr<ASTNode>> Parse();

private:
    std::unique_ptr<Statement> ParseStatement();
    std::unique_ptr<Statement> ParseAssignment();
    std::unique_ptr<Statement> ParseIfStatement();
    std::unique_ptr<Statement> ParseWhileStatement();
    std::unique_ptr<Expression> ParseExpression();
    std::unique_ptr<Expression> ParseBinaryExpression(int minPrecedence);
    std::unique_ptr<Expression> ParseUnaryExpression();
    std::unique_ptr<Expression> ParsePrimaryExpression();

    void Advance() { current_token_ = tokens_[++position_]; }

    [[nodiscard]] bool IsBinaryOp() const noexcept {
        return current_token_.type_ == TokenType::LESS || current_token_.type_ == TokenType::MORE ||
               current_token_.type_ == TokenType::PLUS || current_token_.type_ == TokenType::MINUS ||
               current_token_.type_ == TokenType::MULTIPLY ||
               current_token_.type_ == TokenType::DIVIDE;
    }

    static int GetPrecedence(Token const& token) {
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

    Token current_token_;
    std::vector<Token> tokens_;
    size_t position_;
};
#endif
