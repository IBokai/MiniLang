#include "parser.h"

#include "stdexcept"
// TODO: add EOF token and rewrite position < tokens.size() to current_token.type != TokenType::EOF
std::vector<std::unique_ptr<ASTNode>> Parser::parse() {
    std::vector<std::unique_ptr<ASTNode>> AST;
    while (position < tokens_.size()) {
        current_token = advance();
        if (current_token.type == TokenType::VAR) {
            AST.push_back(std::move(parseAssignemt()));
        } else if (current_token.type == TokenType::IF) {
            AST.push_back(std::move(parseIfStatement()));
        } else if (current_token.type == TokenType::WHILE) {
            AST.push_back(std::move(parseWhileStatement()));
        }
    }
    return AST;
}

std::unique_ptr<ASTNode> Parser::parseAssignemt() {
    std::string varname = current_token.text;
    current_token = advance();
    if (current_token.type != TokenType::ASSIGNMENT) {
        throw std::runtime_error("Assignemt sign expected");
    }
    std::unique_ptr<Expression> expression = parseExpression();
    return std::make_unique<AssignmentStatement>(
            AssignmentStatement(std::move(varname), std::move(expression)));
}

std::unique_ptr<Expression> Parser::parseExpression() { return parseBinaryExpression(); }

std::unique_ptr<Expression> Parser::parseBinaryExpression() {
    std::unique_ptr<Expression> left = parseUnaryExpression();
    return left;
}

std::unique_ptr<Expression> Parser::parseUnaryExpression() {
    current_token = advance();
    if (current_token.type == TokenType::INT) {
        return std::make_unique<NumberExpression>(NumberExpression(std::stoi(current_token.text)));
    } else if (current_token.type == TokenType::VAR) {
        return std::make_unique<VariableExpression>(VariableExpression(current_token.text));
    }
    throw std::runtime_error("Unexpected symbol, while parsing unary expression");
}

std::unique_ptr<ASTNode> Parser::parseIfStatement() { return nullptr; }

std::unique_ptr<ASTNode> Parser::parseWhileStatement() { return nullptr; }