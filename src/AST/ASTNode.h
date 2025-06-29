#ifndef AST_NODE_H
#define AST_NODE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../code-generation/symboltable.h"
#include "../config/config.h"
#include "../token/token.h"

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string GetCode(SymbolTable& table, CompilerConfig& config) {
        switch (config.GetLanguage()) {
            case Language::C:
                return this->GetC(table, config);
                break;
            case Language::RISC:
                return "";
            default:
                break;
        }
        return "";
    };

private:
    virtual std::string GetC(SymbolTable& table, CompilerConfig& config) = 0;
};
#endif
