#include "../exceptions/exceptions.h"
#include "parser.h"

namespace compiler::parser {

using namespace exceptions;

std::unique_ptr<Expression> Parser::ParseExpression() { return ParseBinaryExpression(0); }

std::unique_ptr<Expression> Parser::ParseBinaryExpression(int minPrecedence) {
    auto left = ParseUnaryExpression();
    while (true) {
        Token op = current_token_;
        if (!IsBinaryOp()) {
            break;
        }
        int const precedence = GetPrecedence(op);
        if (precedence < minPrecedence) {
            break;
        }
        Advance();
        auto right = ParseBinaryExpression(precedence + 1);
        left = std::make_unique<BinaryExpression>(std::move(left), op, std::move(right));
    }
    return left;
}

std::unique_ptr<Expression> Parser::ParseUnaryExpression() {
    if (current_token_.type_ == TokenType::MINUS) {
        Advance();
        return std::make_unique<UnaryExpression>(ParsePrimaryExpression(), true);
    }
    return ParsePrimaryExpression();
}

std::unique_ptr<Expression> Parser::ParsePrimaryExpression() {
    if (current_token_.type_ == TokenType::LPAREN) {
        Advance();
        auto inner_expression = ParseExpression();
        if (current_token_.type_ != TokenType::RPAREN) {
            throw CompilerException("Syntax error at (" +
                                    std::to_string(current_token_.position_.first) + " " +
                                    std::to_string(current_token_.position_.second) +
                                    "): expected ')', but got '" + current_token_.text_ + "'");
        }
        Advance();
        return inner_expression;
    }
    if (current_token_.type_ == TokenType::INT) {
        auto result = std::make_unique<NumberExpression>(std::stoi(current_token_.text_));
        Advance();
        return result;
    }
    if (current_token_.type_ == TokenType::VAR) {
        auto result = std::make_unique<VariableExpression>(current_token_.text_);
        Advance();
        return result;
    }
    throw CompilerException("Syntax error at (" + std::to_string(current_token_.position_.first) +
                            " " + std::to_string(current_token_.position_.second) +
                            "): expected number, variable, or '(', but got '" +
                            current_token_.text_ + "'");
}

}  // namespace compiler::parser