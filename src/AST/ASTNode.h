#ifndef AST_NODE_H
#define AST_NODE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../code-generation/register-allocator.h"
#include "../code-generation/symboltable.h"
#include "../configs/configs.h"
#include "../lexer/token/token.h"

namespace compiler::ast {
using namespace codegenerator;
using namespace lexer;
struct RiscCodegenOutput {
    std::string code;
    std::optional<std::string> reg;
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string GetC(SymbolTable& table, configs::FormattingConfig& formatting_config) = 0;
    virtual RiscCodegenOutput GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                                      configs::FormattingConfig& formatting_config) = 0;
};
}  // namespace compiler::ast

#endif
