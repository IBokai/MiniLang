#include "parser.h"

#include <stdexcept>

#include "../AST/ASTNode.h"

std::vector<std::unique_ptr<ASTNode>> Parser::parse() {
    std::vector<std::unique_ptr<ASTNode>> AST;
    while (current_token.type != TokenType::ENDFILE) {
        AST.push_back(parseStatement());
    }
    return AST;
}
