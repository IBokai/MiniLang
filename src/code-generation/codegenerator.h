#pragma once

#include "../AST/ASTNode.h"
#include "../AST/expressions.h"
#include "../AST/statements.h"

class CodeGenerator {
public:
    explicit CodeGenerator(CompilerConfig& config) : config_(config) {}
    std::string Generate(std::vector<std::unique_ptr<ASTNode>> const& ast) {
        switch (config_.GetLanguage()) {
            case Language::C:
                return this->GenerateC(ast);
                break;
            case Language::RISC:
                return this->GenerateRisc(ast);
                break;
            default:
                break;
        }
        throw std::runtime_error("Unknown language");
    }

private:
    CompilerConfig config_;
    std::string GenerateC(std::vector<std::unique_ptr<ASTNode>> const& ast) {
        std::string code = "int main() {\n";

        FormattingConfig formatting_config = FormattingConfig();
        SymbolTable table = SymbolTable();

        formatting_config.AdvanceIndent();
        for (auto const& node : ast) {
            code += node->GetC(table, formatting_config);
            code += '\n';
        }
        code += "}";
        return code;
    }

    std::string GenerateRisc(std::vector<std::unique_ptr<ASTNode>> const& ast) {
        std::string code = "";
        SymbolTable table = SymbolTable();
        RegisterAllocator allocator = RegisterAllocator();
        for (auto const& node : ast) {
            code += node->GetRisc(table, allocator).code;
        }
        return code;
    }
};