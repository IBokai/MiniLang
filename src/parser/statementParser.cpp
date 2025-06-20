#include "parser.h"

std::unique_ptr<Statement> Parser::parseStatement() {
    if (current_token.type_ == TokenType::VAR) {
        auto result = parseAssignment();
        if (current_token.type_ != TokenType::SEMICOL) {
            std::cout << current_token.text_ << '\n';
            throw std::runtime_error("Expected semicolon after assignment statement");
        }
        advance();
        return result;
    } else if (current_token.type_ == TokenType::IF) {
        return parseIfStatement();
    } else if (current_token.type_ == TokenType::WHILE) {
        return parseWhileStatement();
    } else {
        throw std::runtime_error("Expected statement");
    }
}

std::unique_ptr<Statement> Parser::parseAssignment() {
    std::string const varname = current_token.text_;
    advance();
    if (current_token.type_ != TokenType::ASSIGNMENT) {
        throw std::runtime_error("Expected assignment sign after variable name");
    }
    advance();
    return std::make_unique<AssignmentStatement>(varname, parseExpression());
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
    advance();
    auto condition = parseExpression();
    if (current_token.type_ != TokenType::THEN) {
        throw std::runtime_error(
                "Expected then keyword after condition expression in if statement");
    }
    advance();
    std::vector<std::unique_ptr<Statement>> body;
    while (current_token.type_ != TokenType::FI) {
        if (current_token.type_ == TokenType::ENDFILE) {
            throw std::runtime_error("Expected fi keyword before the end of the program");
        }
        body.push_back(parseStatement());
    }
    advance();
    return std::make_unique<IfStatement>(std::move(condition), std::move(body));
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
    advance();
    auto condition = parseExpression();
    if (current_token.type_ != TokenType::DO) {
        throw std::runtime_error(
                "Expected do keyword after condition epxression in while statement");
    }
    advance();
    std::vector<std::unique_ptr<Statement>> body;
    while (current_token.type_ != TokenType::DONE) {
        if (current_token.type_ == TokenType::ENDFILE) {
            throw std::runtime_error("Expected done keyword before the end of the program");
        }
        body.push_back(parseStatement());
    }
    advance();
    return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
}
