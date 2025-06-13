#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "ASTNode.h"

class Expression : public ASTNode {
public:
    void printInfo() override { std::cout << "Expression: "; }
    int calculate() override { return 0; }
};

class NumberExpression final : public Expression {
public:
    explicit NumberExpression(int const value) : value_(value) {}
    void printInfo() override {
        std::cout << "Im Number expression\n";
        std::cout << "value:" << value_ << '\n';
    };

    int calculate() override { return value_; }

private:
    int value_;
};

class VariableExpression final : public Expression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}
    void printInfo() override {
        std::cout << "Im Variable expression\n";
        std::cout << "name:" << name_ << '\n';
    }
    int calculate() override { return 0; }

private:
    std::string name_;
};

class BinaryExpression final : public Expression {
public:
    explicit BinaryExpression(std::unique_ptr<Expression> left, TokenType op,
                              std::unique_ptr<Expression> right)
        : left_(std::move(left)), op_(op), right_(std::move(right)) {}
    void printInfo() override {
        std::cout << "Im Binary expression\n";
        std::cout << "left:\n";
        left_->printInfo();
        std::cout << "right:\n";
        right_->printInfo();
    }

    int calculate() override {
        switch (op_) {
            case TokenType::PLUS:
                return left_->calculate() + right_->calculate();
                break;
            case TokenType::MINUS:
                return left_->calculate() - right_->calculate();
                break;
            case TokenType::MULTIPLY:
                return left_->calculate() * right_->calculate();
                break;
            case TokenType::DIVIDE:
                return left_->calculate() / right_->calculate();
                break;
            case TokenType::LESS:
                return left_->calculate() < right_->calculate();
            case TokenType::MORE:
                return left_->calculate() > right_->calculate();
            default:
                break;
        }
        return 0;
    }

private:
    std::unique_ptr<Expression> left_;
    TokenType op_;
    std::unique_ptr<Expression> right_;
};

class UnaryExpression : public Expression {
public:
    UnaryExpression(std::unique_ptr<Expression> expression, bool negative = false)
        : expression_(std::move(expression)), negative_(negative) {}

private:
    std::unique_ptr<Expression> expression_;
    bool negative_;
};
#endif
