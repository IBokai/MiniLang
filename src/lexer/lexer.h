#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <vector>

#include "../token/token.h"

class Lexer {
public:
    explicit Lexer(std::string const& filename);
    std::vector<Token> Tokenize();

private:
    Token TokenizeNumber();
    Token TokenizeVarOrKeyword();
    Token TokenizeSemicolon();
    Token TokenizeOperator();
    std::ifstream file_;
    std::string line_;
    size_t line_index_;
    size_t position_;
};
#endif