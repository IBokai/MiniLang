#include "parser.h"
namespace compiler::parser {
std::unique_ptr<Statement> Parser::ParseStatement() {
    if (current_token_.type_ == TokenType::VAR) {
        auto result = ParseAssignment();
        if (current_token_.type_ != TokenType::SEMICOL) {
            std::cout << current_token_.text_ << '\n';
            throw std::runtime_error("Expected semicolon after assignment statement");
        }
        Advance();
        return result;
    } else if (current_token_.type_ == TokenType::IF) {
        return ParseIfStatement();
    } else if (current_token_.type_ == TokenType::WHILE) {
        return ParseWhileStatement();
    } else {
        throw std::runtime_error("Expected statement");
    }
}

std::unique_ptr<Statement> Parser::ParseAssignment() {
    std::string const varname = current_token_.text_;
    Advance();
    if (current_token_.type_ != TokenType::ASSIGNMENT) {
        throw std::runtime_error("Expected assignment sign after variable name");
    }
    Advance();
    return std::make_unique<AssignmentStatement>(varname, ParseExpression());
}

std::unique_ptr<Statement> Parser::ParseIfStatement() {
    Advance();
    auto condition = ParseExpression();
    if (current_token_.type_ != TokenType::THEN) {
        throw std::runtime_error(
            "Expected then keyword after condition expression in if statement");
    }
    Advance();
    std::vector<std::unique_ptr<Statement>> body;
    while (current_token_.type_ != TokenType::FI) {
        if (current_token_.type_ == TokenType::ENDFILE) {
            throw std::runtime_error("Expected fi keyword before the end of the program");
        }
        body.push_back(ParseStatement());
    }
    Advance();
    return std::make_unique<IfStatement>(std::move(condition), std::move(body));
}

std::unique_ptr<Statement> Parser::ParseWhileStatement() {
    Advance();
    auto condition = ParseExpression();
    if (current_token_.type_ != TokenType::DO) {
        throw std::runtime_error(
            "Expected do keyword after condition epxression in while statement");
    }
    Advance();
    std::vector<std::unique_ptr<Statement>> body;
    while (current_token_.type_ != TokenType::DONE) {
        if (current_token_.type_ == TokenType::ENDFILE) {
            throw std::runtime_error("Expected done keyword before the end of the program");
        }
        body.push_back(ParseStatement());
    }
    Advance();
    return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
}
}  // namespace compiler::parser
