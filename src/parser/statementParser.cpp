#include "../exceptions/exceptions.h"
#include "parser.h"

namespace compiler::parser {

using namespace exceptions;

std::unique_ptr<Statement> Parser::ParseStatement() {
    if (current_token_.type_ == TokenType::VAR) {
        auto result = ParseAssignment();
        if (current_token_.type_ != TokenType::SEMICOL) {
            throw CompilerException(
                "Syntax error at (" + std::to_string(current_token_.position_.first) + " " +
                std::to_string(current_token_.position_.second) +
                "): expected ';' after assignment, but got '" + current_token_.text_ + "'");
        }
        Advance();
        return result;
    } else if (current_token_.type_ == TokenType::IF) {
        return ParseIfStatement();
    } else if (current_token_.type_ == TokenType::WHILE) {
        return ParseWhileStatement();
    } else {
        throw CompilerException(
            "Syntax error at (" + std::to_string(current_token_.position_.first) + " " +
            std::to_string(current_token_.position_.second) +
            "): expected identifier, 'if', or 'while', but got '" + current_token_.text_ + "'");
    }
}

std::unique_ptr<Statement> Parser::ParseAssignment() {
    std::string const varname = current_token_.text_;
    Advance();
    if (current_token_.type_ != TokenType::ASSIGNMENT) {
        throw CompilerException(
            "Syntax error at (" + std::to_string(current_token_.position_.first) + " " +
            std::to_string(current_token_.position_.second) +
            "): expected '=' after variable name, but got '" + current_token_.text_ + "'");
    }
    Advance();
    return std::make_unique<AssignmentStatement>(varname, ParseExpression());
}

std::unique_ptr<Statement> Parser::ParseIfStatement() {
    Advance();
    auto condition = ParseExpression();
    if (current_token_.type_ != TokenType::THEN) {
        throw CompilerException("Syntax error at (" +
                                std::to_string(current_token_.position_.first) + " " +
                                std::to_string(current_token_.position_.second) +
                                "): expected 'then' after condition in 'if' statement, but got '" +
                                current_token_.text_ + "'");
    }
    Advance();
    std::vector<std::unique_ptr<Statement>> body;
    while (current_token_.type_ != TokenType::FI) {
        if (current_token_.type_ == TokenType::ENDFILE) {
            throw CompilerException("Syntax error at (" +
                                    std::to_string(current_token_.position_.first) + " " +
                                    std::to_string(current_token_.position_.second) +
                                    "): expected 'fi' at end of 'if' statement, but got '" +
                                    current_token_.text_ + "'");
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
        throw CompilerException("Syntax error at (" +
                                std::to_string(current_token_.position_.first) + " " +
                                std::to_string(current_token_.position_.second) +
                                "): expected 'do' after condition in 'while' statement, but got '" +
                                current_token_.text_ + "'");
    }
    Advance();
    std::vector<std::unique_ptr<Statement>> body;
    while (current_token_.type_ != TokenType::DONE) {
        if (current_token_.type_ == TokenType::ENDFILE) {
            throw CompilerException("Syntax error at (" +
                                    std::to_string(current_token_.position_.first) + " " +
                                    std::to_string(current_token_.position_.second) +
                                    "): expected 'done' at end of 'while' statement, but got '" +
                                    current_token_.text_ + "'");
        }
        body.push_back(ParseStatement());
    }
    Advance();
    return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
}
}  // namespace compiler::parser
