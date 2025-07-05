#include "parser.h"

#include <stdexcept>

#include "../AST/ASTNode.h"
namespace compiler::parser {
std::vector<std::unique_ptr<ASTNode>> Parser::Parse() {
    std::vector<std::unique_ptr<ASTNode>> ast;
    while (current_token_.type_ != TokenType::ENDFILE) {
        ast.push_back(ParseStatement());
    }
    return ast;
}
}  // namespace compiler::parser
