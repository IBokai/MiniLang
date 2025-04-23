#include <fstream>
#include <iostream>
#include <string>

#include "lexer/lexer.h"
#include "AST/ASTNode.h"

int main() {
    std::unique_ptr<Expression> left = std::make_unique<NumberExpression>(NumberExpression(3));
    std::string name = "name";
    std::unique_ptr<Statement> assign = std::make_unique<AssignmentStatement>(AssignmentStatement(std::move(name), std::move(left)));
//     Lexer lexer("../samples/basic.txt");
//     auto v = lexer.Tokenize();
//     std::cout << v.size() << '\n';
//     for (int i = 0; i < v.size(); i++) {
//         std::cout << v[i].text << '\n';
//     }
//     return 0;
}