#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "../../AST/ASTNode.h"
#include "../../AST/expressions.h"
#include "../../AST/statements.h"
#include "../../configs/configs.h"

namespace compiler::codegenerator {

using namespace ast;

class ICodeGenerator : public ASTVisitor {
public:
    virtual std::string Generate(std::vector<std::unique_ptr<ASTNode>> const& ast) = 0;
    virtual ~ICodeGenerator() = default;
};

template <configs::Language>
class CodeGenerator : public ICodeGenerator {
    CodeGenerator() = delete;
};
}  // namespace compiler::codegenerator
#endif