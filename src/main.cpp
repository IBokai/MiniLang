#include <fstream>
#include <iostream>
#include <string>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "util/processinput.h"

int main(int argc, char* argv[]) {
    std::string const input = processinput(argv, argc);
    Lexer lexer(input);
    auto const Tokens = lexer.Tokenize();
    for (auto& token : Tokens) {
        std::cout << token.text_ << ' ' << token.position_.first << ' ' << token.position_.second
                  << '\n';
    }
    Parser p(Tokens);
    auto const AST = p.parse();
    std::cout << AST.size() << '\n';
    return 0;
}