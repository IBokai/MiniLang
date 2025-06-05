#include "parser.h"

std::unique_ptr<Expression> Parser::parseExpression() {
    return parseBinaryExpression(0);
}

std::unique_ptr<Expression> Parser::parseBinaryExpression(int minPrecedence) {
    auto left = parseUnaryExpression();
    while (true) {
        Token op = current_token;
        if (!isBinaryOP()) {
            break;
        }
        int const precedence = getPrecedence(op);
        if (precedence < minPrecedence) {
            break;
        }
        advance();
        auto right = parseBinaryExpression(precedence + 1);
        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }
    return left;
}

std::unique_ptr<Expression> Parser::parseUnaryExpression() {
    if (current_token.type == TokenType::INT) {
        auto result = std::make_unique<NumberExpression>(std::stoi(current_token.text));
        advance();
        return result;
    }
    if (current_token.type == TokenType::VAR) {
        auto result = std::make_unique<VariableExpression>(current_token.text);
        advance();
        return result;
    }
    throw std::runtime_error("Expected number or variable");
}