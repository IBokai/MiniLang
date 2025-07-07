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

// definitions for ASTvisitor
class NumberExpression;
class VariableExpression;
class BinaryExpression;
class UnaryExpression;
class AssignmentStatement;
class IfStatement;
class WhileStatement;

class ASTVisitor {
public:
    virtual void Visit(NumberExpression const* node) = 0;
    virtual void Visit(VariableExpression const* node) = 0;
    virtual void Visit(BinaryExpression const* node) = 0;
    virtual void Visit(UnaryExpression const* node) = 0;
    virtual void Visit(AssignmentStatement const* node) = 0;
    virtual void Visit(IfStatement const* node) = 0;
    virtual void Visit(WhileStatement const* node) = 0;
    virtual ~ASTVisitor() = default;
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void Accept(ASTVisitor* visitor) = 0;
};
}  // namespace compiler::ast
#endif
