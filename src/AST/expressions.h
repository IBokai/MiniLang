#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "ASTNode.h"
namespace compiler::ast {
using namespace lexer;
class Expression : public ASTNode {
public:
    void Accept(ASTVisitor* visitor) override = 0;
};

class NumberExpression final : public Expression {
public:
    explicit NumberExpression(int const value) : value_(value) {}

    int const& GetValue() const { return value_; }
    void Accept(ASTVisitor* visitor) override { visitor->Visit(this); }

private:
    int value_;
};

class VariableExpression final : public Expression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

    std::string const& GetName() const { return name_; }

    void Accept(ASTVisitor* visitor) override { visitor->Visit(this); }

private:
    std::string name_;
};

class BinaryExpression final : public Expression {
public:
    explicit BinaryExpression(std::unique_ptr<Expression> left, Token op,
                              std::unique_ptr<Expression> right)
        : left_(std::move(left)), op_(std::move(op)), right_(std::move(right)) {}

    std::unique_ptr<Expression> const& GetLeftExpression() const { return left_; }
    std::unique_ptr<Expression> const& GetRightExpression() const { return right_; }
    Token const& GetOP() const { return op_; }

    void Accept(ASTVisitor* visitor) override { visitor->Visit(this); }

private:
    std::unique_ptr<Expression> left_;
    Token op_;
    std::unique_ptr<Expression> right_;
};

class UnaryExpression : public Expression {
public:
    explicit UnaryExpression(std::unique_ptr<Expression> expression, bool negative = false)
        : expression_(std::move(expression)), negative_(negative) {}

    std::unique_ptr<Expression> const& GetExpression() const { return expression_; }
    bool IsNegative() const { return negative_; }

    void Accept(ASTVisitor* visitor) override { visitor->Visit(this); };

private:
    std::unique_ptr<Expression> expression_;
    bool negative_;
};
}  // namespace compiler::ast
#endif
