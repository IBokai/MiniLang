#include <fstream>
#include <iostream>
#include <string>

#include "lexer/lexer.h"
#include "AST/ASTNode.h"
#include "parser/parser.h"
#include "util/processinput.h"

int main(int argc, char* argv[]) {
    std::string input = processinput(argv, argc);
    Lexer lexer(input);
    auto Tokens = lexer.Tokenize();
    for(auto& token : Tokens){
        std::cout << token.text << '\n';
    }
    //Parser p(Tokens);
    //auto AST = p.parse();
    return 0;
}