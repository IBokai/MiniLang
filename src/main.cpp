#include <fstream>
#include <iostream>
#include <string>

#include "lexer/lexer.h"
#include "AST/ASTNode.h"

int main() {
    Lexer lexer("../samples/basic.txt");
    auto v = lexer.Tokenize();
    std::cout << v.size() << '\n';
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i].text << '\n';
    }
    return 0;
}