#ifndef AST_NODE_H
#define AST_NODE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../token/token.h"

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void printInfo() = 0;
    virtual int calculate() = 0;
};

class Expression : public ASTNode {
public:
    void printInfo() override { std::cout << "Expression: "; }
    int calculate() override { return 0; }
};

class Statement : public ASTNode {
public:
    void printInfo() override { std::cout << "Statement: "; }
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

class AssignmentStatement final : public Statement {
public:
    explicit AssignmentStatement(std::string name, std::unique_ptr<Expression> expression)
        : name_(std::move(name)), expression_(std::move(expression)) {}
    void printInfo() override {
        std::cout << "Im Assignment statement\n";
        std::cout << "Variable name:" << name_ << '\n';
        expression_->printInfo();
    };

    int calculate() override { return expression_->calculate(); }

private:
    std::string name_;
    std::unique_ptr<Expression> expression_;
};

class IfStatement final : public Statement {
public:
    explicit IfStatement(std::unique_ptr<Expression> condition,
                         std::vector<std::unique_ptr<Statement>> body)
        : condition_(std::move(condition)), body_(std::move(body)) {}
    void printInfo() override {}

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;
};

class WhileStatement final : public Statement {
public:
    explicit WhileStatement(std::unique_ptr<Expression> condition,
                            std::vector<std::unique_ptr<Statement>> body)
        : condition_(std::move(condition)), body_(std::move(body)) {}
    void printInfo() override {}

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;
};
#endif
