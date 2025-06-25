#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "ASTNode.h"

class Expression : public ASTNode {};

class NumberExpression final : public Expression {
public:
    explicit NumberExpression(int const value) : value_(value) {}

    int const& getValue() const { return value_; }

private:
    int value_;
};

class VariableExpression final : public Expression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

    std::string const& getName() const { return name_; }

private:
    std::string name_;
};

class BinaryExpression final : public Expression {
public:
    explicit BinaryExpression(std::unique_ptr<Expression> left, TokenType op,
                              std::unique_ptr<Expression> right)
        : left_(std::move(left)), op_(op), right_(std::move(right)) {}

    std::unique_ptr<Expression> const& getLeftExpression() const { return left_; }
    std::unique_ptr<Expression> const& getRightExpression() const { return right_; }
    TokenType const& getOP() const { return op_; }

private:
    std::unique_ptr<Expression> left_;
    TokenType op_;
    std::unique_ptr<Expression> right_;
};

class UnaryExpression : public Expression {
public:
    explicit UnaryExpression(std::unique_ptr<Expression> expression, bool negative = false)
        : expression_(std::move(expression)), negative_(negative) {}

    std::unique_ptr<Expression> const& getExpression() const { return expression_; }
    bool isNegative() const { return negative_; }

private:
    std::unique_ptr<Expression> expression_;
    bool negative_;
};
#endif
