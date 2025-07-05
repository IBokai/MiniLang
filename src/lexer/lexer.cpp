#include "lexer.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace compiler::lexer {
std::unordered_map<std::string, TokenType> keyword_types{
    {"if", TokenType::IF},       {"fi", TokenType::FI}, {"then", TokenType::THEN},
    {"while", TokenType::WHILE}, {"do", TokenType::DO}, {"done", TokenType::DONE}};

std::unordered_map<std::string, TokenType> operator_types{
    {"=", TokenType::ASSIGNMENT}, {"+", TokenType::PLUS},     {"-", TokenType::MINUS},
    {"/", TokenType::DIVIDE},     {"*", TokenType::MULTIPLY}, {"<", TokenType::LESS},
    {">", TokenType::MORE},       {"(", TokenType::LPAREN},   {")", TokenType::RPAREN}};

std::vector<Token> Lexer::Tokenize() {
    std::vector<Token> result;
    std::unordered_set<char> operators = {'=', '+', '-', '/', '*', '<', '>', '(', ')'};
    while (std::getline(file_, line_)) {
        while (position_ != line_.length()) {
            if (isspace(line_[position_])) {
                position_++;
                if (position_ >= line_.size()) {
                    break;
                }
            } else if (isalpha(line_[position_])) {
                result.push_back(TokenizeVarOrKeyword());
                if (position_ >= line_.size()) {
                    break;
                }
            } else if (isdigit(line_[position_])) {
                result.push_back(TokenizeNumber());
                if (position_ >= line_.size()) {
                    break;
                }
            } else if (line_[position_] == ';') {
                result.push_back(TokenizeSemicolon());
                if (position_ >= line_.size()) {
                    break;
                }
            } else if (operators.count(line_[position_])) {
                result.push_back(TokenizeOperator());
                if (position_ >= line_.size()) {
                    break;
                }
            } else {
                throw std::runtime_error("Unexpected symbol");
            }
        }
        position_ = 0;
        line_index_++;
    }
    file_.close();
    result.push_back(Token(TokenType::ENDFILE, "EOF", {line_index_, position_}));
    return result;
}

Token Lexer::TokenizeNumber() {
    std::string token_text;
    size_t starting_posistion = position_;
    while (isdigit(line_[position_])) {
        token_text += line_[position_];
        position_++;
    }
    if (!isalpha(line_[position_])) {
        return {TokenType::INT, token_text, {line_index_, starting_posistion}};
    }
    throw std::runtime_error("error tokenizing NUMBER");
}

Token Lexer::TokenizeVarOrKeyword() {
    std::string token_text;
    size_t starting_position = position_;
    std::unordered_set<std::string> keywords = {"if", "fi", "then", "while", "do", "done"};
    while (isalpha(line_[position_]) || isdigit(line_[position_])) {
        token_text += line_[position_];
        position_++;
    }
    if (keywords.count(token_text)) {
        if (!isalpha(line_[position_]) && !isdigit(line_[position_])) {
            return {keyword_types.at(token_text), token_text, {line_index_, starting_position}};
        } else {
            throw std::runtime_error("error tokenizing VAR or KEYWORD");
        }
    }
    return {TokenType::VAR, token_text, {line_index_, starting_position}};
}

Token Lexer::TokenizeSemicolon() {
    size_t starting_position = position_;
    position_++;
    return {TokenType::SEMICOL, ";", {line_index_, starting_position}};
}

Token Lexer::TokenizeOperator() {
    std::string token_text;
    size_t starting_position = position_;
    token_text += line_[position_];
    position_++;
    return {operator_types.at(token_text), token_text, {line_index_, starting_position}};
}

Lexer::Lexer(std::string const& filename) {
    file_.open(filename);
    if (!file_) {
        throw std::runtime_error("Error, while processing file");
    }
    position_ = 0;
    line_index_ = 0;
}
}  // namespace compiler::lexer