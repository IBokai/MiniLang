#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "../AST/ASTNode.h"
#include "../configs/configs.h"

namespace compiler::codegenerator {
using namespace ast;
class CodeGenerator {
public:
    explicit CodeGenerator(configs::Language language) : language_(language) {}
    std::string Generate(std::vector<std::unique_ptr<ASTNode>> const& ast) {
        switch (language_) {
            case configs::Language::C:
                return this->GenerateC(ast);
                break;
            case configs::Language::RISC:
                return this->GenerateRisc(ast);
                break;
            default:
                break;
        }
        throw std::runtime_error("Unknown language");
    }

private:
    configs::Language language_;

    std::string GenerateC(std::vector<std::unique_ptr<ASTNode>> const& ast);
    std::string GenerateRisc(std::vector<std::unique_ptr<ASTNode>> const& ast);
};
}  // namespace compiler::codegenerator
#endif