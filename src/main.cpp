#include <fstream>
#include <iostream>
#include <string>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "util/processinput.h"

int main(int argc, char* argv[]) {
    std::string const input = ProcessInput(argv, argc);
    Lexer lexer(input);
    auto const tokens = lexer.Tokenize();
    for (auto const& token : tokens) {
        std::cout << token.text_ << ' ' << token.position_.first << ' ' << token.position_.second
                  << '\n';
    }
    Parser p(tokens);
    auto const ast = p.Parse();
    std::cout << ast.size() << '\n';
    return 0;
}