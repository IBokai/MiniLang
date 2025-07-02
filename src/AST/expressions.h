#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "ASTNode.h"

class Expression : public ASTNode {
public:
    std::string GetC(SymbolTable& symbol_table, FormattingConfig& formatting_config) override = 0;
    RiscCodegenOutput GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                              FormattingConfig&) override = 0;
};

class NumberExpression final : public Expression {
public:
    explicit NumberExpression(int const value) : value_(value) {}

    int const& GetValue() const { return value_; }

    std::string GetC([[maybe_unused]] SymbolTable& table,
                     [[maybe_unused]] FormattingConfig& formatting_config) override;

    RiscCodegenOutput GetRisc([[maybe_unused]] SymbolTable& table, RegisterAllocator& allocator,
                              FormattingConfig& formatting_config) override;

private:
    int value_;
};

class VariableExpression final : public Expression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

    std::string const& GetName() const { return name_; }

    std::string GetC(SymbolTable& table,
                     [[maybe_unused]] FormattingConfig& formatting_config) override;

    RiscCodegenOutput GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                              FormattingConfig& formatting_config) override;

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

    std::string GetC(SymbolTable& table, FormattingConfig& formatting_config) override;

    RiscCodegenOutput GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                              FormattingConfig& formatting_config) override;

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

    std::string GetC(SymbolTable& table, FormattingConfig& formatting_config) override;

    RiscCodegenOutput GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                              FormattingConfig& formatting_config) override;

private:
    std::unique_ptr<Expression> expression_;
    bool negative_;
};
#endif
