#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <vector>

#include "../token/token.h"

class Lexer {
public:
    Lexer(std::string filename);
    std::vector<Token> Tokenize();

private:
    Token TokenizeNumber();
    Token TokenizeVarOrKeyword();
    Token TokenizeSemicol();
    Token TokenizeOperator();
    std::string text;
    int position;
};
#endif