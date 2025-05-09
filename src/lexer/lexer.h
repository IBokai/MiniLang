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
    Token TokenizeSemicol();
    Token TokenizeOperator();
    std::ifstream file;
    std::string line;
    size_t position;
};
#endif