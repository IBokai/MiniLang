#pragma once

#include "../AST/ASTNode.h"
#include "../AST/expressions.h"
#include "../AST/statements.h"

class CodeGenerator {
public:
    explicit CodeGenerator(CompilerConfig& config) : config_(config) {}
    std::string Generate(std::vector<std::unique_ptr<ASTNode>> const& ast) {
        std::string code = config_.GetIndent() + "int main() {\n";
        SymbolTable table = SymbolTable();
        config_.AdvanceIndent();
        for (auto const& node : ast) {
            code += node->GetCode(table, config_);
            code += '\n';
        }
        code += "}";
        return code;
    }

private:
    CompilerConfig config_;
};