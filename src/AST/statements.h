#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "ASTNode.h"
#include "expressions.h"

class Statement : public ASTNode {
private:
    std::string GetC(SymbolTable& symbol_table, CompilerConfig& config) override = 0;
};

class AssignmentStatement final : public Statement {
public:
    explicit AssignmentStatement(std::string name, std::unique_ptr<Expression> expression)
        : name_(std::move(name)), expression_(std::move(expression)) {}

    std::unique_ptr<Expression> const& GetExpression() const { return expression_; }
    std::string const& GetName() const { return name_; }

private:
    std::string name_;
    std::unique_ptr<Expression> expression_;

    std::string GetC(SymbolTable& table, CompilerConfig& config) override {
        if (!table.CheckSymbol(name_)) {
            std::string result = config.GetIndent() + "int " + name_ + " = ";
            result += expression_->GetCode(table, config);
            result += ";";
            table.AddSymbol(name_);
            return result;
        } else {
            std::string result = config.GetIndent() + name_ + " = ";
            result += expression_->GetCode(table, config);
            result += ";";
            return result;
        }
    };
};

class IfStatement final : public Statement {
public:
    explicit IfStatement(std::unique_ptr<Expression> condition,
                         std::vector<std::unique_ptr<Statement>> body)
        : condition_(std::move(condition)), body_(std::move(body)) {}

    std::unique_ptr<Expression> const& GetCondition() const { return condition_; }
    std::vector<std::unique_ptr<Statement>> const& GetBody() const { return body_; }

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;

    std::string GetC(SymbolTable& table, CompilerConfig& config) override {
        std::string code =
            config.GetIndent() + "if (" + condition_->GetCode(table, config) + ") {\n";
        config.AdvanceIndent();
        SymbolTable local_table = table;
        for (auto const& body_statement : body_) {
            code += body_statement->GetCode(local_table, config) + "\n";
        }
        config.DecreaseIndent();
        code += config.GetIndent() + "}";
        return code;
    }
};

class WhileStatement final : public Statement {
public:
    explicit WhileStatement(std::unique_ptr<Expression> condition,
                            std::vector<std::unique_ptr<Statement>> body)
        : condition_(std::move(condition)), body_(std::move(body)) {}

    std::unique_ptr<Expression> const& GetCondition() const { return condition_; }
    std::vector<std::unique_ptr<Statement>> const& GetBody() const { return body_; }

private:
    std::unique_ptr<Expression> condition_;
    std::vector<std::unique_ptr<Statement>> body_;

    std::string GetC(SymbolTable& table, CompilerConfig& config) override {
        std::string code =
            config.GetIndent() + "while (" + condition_->GetCode(table, config) + ") {\n";
        config.AdvanceIndent();
        SymbolTable local_table = table;
        for (auto const& body_statement : body_) {
            code += body_statement->GetCode(local_table, config) + "\n";
        }
        config.DecreaseIndent();
        code += config.GetIndent() + "}";
        return code;
    }
};

#endif
