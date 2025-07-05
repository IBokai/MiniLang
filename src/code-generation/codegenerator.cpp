#include "codegenerator.h"

namespace compiler::codegenerator {
std::string CodeGenerator::GenerateC(std::vector<std::unique_ptr<ASTNode>> const& ast) {
    std::string code = "int main() {\n";

    configs::FormattingConfig formatting_config = configs::FormattingConfig();
    SymbolTable table = SymbolTable();

    formatting_config.AdvanceIndent();
    for (auto const& node : ast) {
        code += node->GetC(table, formatting_config);
        code += '\n';
    }
    code += "}";
    return code;
}

std::string CodeGenerator::GenerateRisc(std::vector<std::unique_ptr<ASTNode>> const& ast) {
    std::string code = ".text\n.global _start\n_start:\n";

    configs::FormattingConfig formatting_config = configs::FormattingConfig();
    SymbolTable table = SymbolTable();
    RegisterAllocator allocator = RegisterAllocator();

    formatting_config.AdvanceIndent();
    for (auto const& node : ast) {
        code += node->GetRisc(table, allocator, formatting_config).code;
    }
    code += formatting_config.GetIndent() + "li a7, 93\necall\n";
    return code;
}
}  // namespace compiler::codegenerator