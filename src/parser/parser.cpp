#include "parser.h"

#include <stdexcept>

#include "../AST/ASTNode.h"

std::vector<std::unique_ptr<ASTNode>> Parser::parse() {
    std::vector<std::unique_ptr<ASTNode>> AST;
    while (current_token.type != TokenType::ENDFILE) {
        AST.push_back(parseStatement());
    }
    return AST;
}

std::unique_ptr<Statement> Parser::parseStatement() {
    if (current_token.type == TokenType::VAR) {
        auto result = parseAssignment();
        if (current_token.type != TokenType::SEMICOL) {
            std::cout << current_token.text << '\n';
            throw std::runtime_error("Expected semicolon after assignment statement");
        }
        advance();
        return result;
    } else if (current_token.type == TokenType::IF) {
        return parseIfStatement();
    } else if (current_token.type == TokenType::WHILE) {
        return parseWhileStatement();
    } else {
        throw std::runtime_error("Expected statement");
    }
}

std::unique_ptr<Statement> Parser::parseAssignment() {
    std::string const varname = current_token.text;
    advance();
    if (current_token.type != TokenType::ASSIGNMENT) {
        throw std::runtime_error("Expected assignment sign after variable name");
    }
    advance();
    return std::make_unique<AssignmentStatement>(varname, parseExpression());
}

std::unique_ptr<Statement> Parser::parseIfStatement() { return nullptr; }

std::unique_ptr<Statement> Parser::parseWhileStatement() { return nullptr; }
