#pragma once
#include <memory>
#include <string>
#include <vector>

class ASTNode {};

class Expression : public ASTNode {};

class Statement : public ASTNode {};

class NumberExpression : public Expression {
public:
    explicit NumberExpression(int const value) : value_(value) {}

private:
    int value_;
};

class VariableExpression : public Expression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

private:
    std::string name_;
};

class BinaryExpression : public Expression {
public:
    explicit BinaryExpression(std::unique_ptr<Expression> left, std::string op,
                     std::unique_ptr<Expression> right)
        : left_(std::move(left)), op_(std::move(op)), right_(std::move(right)) {}

private:
    std::unique_ptr<Expression> left_;
    std::string op_;  // operation, maybe replace it with enum class or something
    std::unique_ptr<Expression> right_;
};

class AssignmentStatement : public Statement {
public:
    explicit AssignmentStatement(std::string name, std::unique_ptr<Expression> expression)
        : name_(std::move(name)), expression_(std::move(expression)) {}

private:
    std::string name_;
    std::unique_ptr<Expression> expression_;
};

class IfStatement : public Statement {
public:
    explicit IfStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> bodyStatement)
        : condition_(std::move(condition)) {
        body_.push_back(std::move(bodyStatement));
    }

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;
};

class WhileStatement : public Statement {
public:
    explicit WhileStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> bodyStatement)
        : condition_(std::move(condition)) {
        body_.push_back(std::move(bodyStatement));
    }

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;
};
