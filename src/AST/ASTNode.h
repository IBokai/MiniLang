#pragma once
#include <memory>
#include <string>
#include <vector>

class ASTNode {};

class Expression : public ASTNode {};

class Statement : public ASTNode {};

class NumberExpression : public Expression {
    int value;
};

class VariableExpression : public Expression {
    std::string name;
};

class BinaryExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::string op;  // operation, maybe replace it with enum class or something
    std::unique_ptr<Expression> right;
};

class AssignmentStatement : public Statement {
    std::string name;
    std::unique_ptr<Expression> expression;
};

class IfStatement : public Statement {
    std::unique_ptr<Expression> condition;
    std::vector<std::unique_ptr<Statement>> body;
};

class WhileStatement : public Statement {
    std::unique_ptr<Expression> condition;
    std::vector<std::unique_ptr<Statement>> body;
};
