#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "ASTNode.h"
#include "expressions.h"

namespace compiler::ast {
class Statement : public ASTNode {
public:
    void Accept(ASTVisitor* visitor) override = 0;
};

class AssignmentStatement final : public Statement {
public:
    explicit AssignmentStatement(std::string name, std::unique_ptr<Expression> expression)
        : name_(std::move(name)), expression_(std::move(expression)) {}

    std::unique_ptr<Expression> const& GetExpression() const { return expression_; }
    std::string const& GetName() const { return name_; }

    void Accept(ASTVisitor* visitor) override { visitor->Visit(this); };

private:
    std::string name_;
    std::unique_ptr<Expression> expression_;
};

class IfStatement final : public Statement {
public:
    explicit IfStatement(std::unique_ptr<Expression> condition,
                         std::vector<std::unique_ptr<Statement>> body)
        : condition_(std::move(condition)), body_(std::move(body)) {}

    std::unique_ptr<Expression> const& GetCondition() const { return condition_; }
    std::vector<std::unique_ptr<Statement>> const& GetBody() const { return body_; }

    void Accept(ASTVisitor* visitor) override { visitor->Visit(this); };

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;
};

class WhileStatement final : public Statement {
public:
    explicit WhileStatement(std::unique_ptr<Expression> condition,
                            std::vector<std::unique_ptr<Statement>> body)
        : condition_(std::move(condition)), body_(std::move(body)) {}

    std::unique_ptr<Expression> const& GetCondition() const { return condition_; }
    std::vector<std::unique_ptr<Statement>> const& GetBody() const { return body_; }

    void Accept(ASTVisitor* visitor) override { visitor->Visit(this); };

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;
};
}  // namespace compiler::ast
#endif
