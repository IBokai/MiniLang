#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "ASTNode.h"

inline std::string OPtostring(TokenType type) {
    switch (type) {
        case TokenType::PLUS:
            return "+";
            break;
        case TokenType::MINUS:
            return "-";
            break;
        case TokenType::MULTIPLY:
            return "*";
            break;
        case TokenType::DIVIDE:
            return "/";
            break;
        case TokenType::LESS:
            return "<";
            break;
        case TokenType::MORE:
            return ">";
            break;
        default:
            break;
    }
    return "";
}

class Expression : public ASTNode {
public:
private:
    std::string GetC(SymbolTable& symbol_table, CompilerConfig& config) override = 0;
};

class NumberExpression final : public Expression {
public:
    explicit NumberExpression(int const value) : value_(value) {}

    int const& GetValue() const { return value_; }

private:
    std::string GetC([[maybe_unused]] SymbolTable& table,
                     [[maybe_unused]] CompilerConfig& config) override {
        return std::to_string(value_);
    }
    int value_;
};

class VariableExpression final : public Expression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

    std::string const& GetName() const { return name_; }

private:
    std::string GetC(SymbolTable& table, [[maybe_unused]] CompilerConfig& config) override {
        if (table.CheckSymbol(name_)) {
            return name_;
        }
        throw std::runtime_error(
            "Error while variable expression, no variable with such name declared");
    }
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

private:
    std::unique_ptr<Expression> left_;
    Token op_;
    std::unique_ptr<Expression> right_;

    std::string GetC(SymbolTable& table, CompilerConfig& config) override {
        return "(" + left_->GetCode(table, config) + " " + OPtostring(op_) + " " +
               right_->GetCode(table, config) + ")";
    }
};

class UnaryExpression : public Expression {
public:
    explicit UnaryExpression(std::unique_ptr<Expression> expression, bool negative = false)
        : expression_(std::move(expression)), negative_(negative) {}

    std::unique_ptr<Expression> const& GetExpression() const { return expression_; }
    bool IsNegative() const { return negative_; }

private:
    std::unique_ptr<Expression> expression_;
    bool negative_;

    std::string GetC(SymbolTable& table, CompilerConfig& config) override {
        if (negative_) {
            return "-" + expression_->GetCode(table, config);
        }
        return expression_->GetCode(table, config);
    };
};
#endif
