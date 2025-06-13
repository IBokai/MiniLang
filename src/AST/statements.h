#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "ASTNode.h"
#include "expressions.h"

class Statement : public ASTNode {
public:
    void printInfo() override { std::cout << "Statement: "; }
    int calculate() override { return 0; }
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
