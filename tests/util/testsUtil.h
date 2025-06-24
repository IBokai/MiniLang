#ifndef TESTSUTIL_H
#define TESTSUTIL_H

#include <gtest/gtest.h>

#include "../../src/AST/ASTNode.h"
#include "../../src/AST/expressions.h"
#include "../../src/AST/statements.h"

template <typename ExpectedT>
struct ASTChecker {
    static ExpectedT* check(ASTNode* node) {
        auto* casted = dynamic_cast<ExpectedT*>(node);
        if (!casted) {
            ADD_FAILURE() << "Expected " << typeid(ExpectedT).name() << ", got "
                          << typeid(*node).name();
        }
        return casted;
    }
};

template <>
struct ASTChecker<AssignmentStatement> {
    static AssignmentStatement* check(ASTNode* node, std::string const& varname) {
        auto* casted = dynamic_cast<AssignmentStatement*>(node);
        if (!casted) {
            ADD_FAILURE() << "Expected Assignment statement '" << typeid(AssignmentStatement).name()
                          << "', got " << typeid(*node).name();
        }
        EXPECT_EQ(casted->getName(), varname);
        return casted;
    }
};

template <>
struct ASTChecker<VariableExpression> {
    static void check(ASTNode* node, std::string const& varname) {
        auto* casted = dynamic_cast<VariableExpression*>(node);
        if (!casted) {
            ADD_FAILURE() << "Expected VariableExpression '" << typeid(VariableExpression).name()
                          << "', got " << typeid(*node).name();
        }
        EXPECT_EQ(casted->getName(), varname);
    }
};

template <>
struct ASTChecker<NumberExpression> {
    static void check(ASTNode* node, int const& value) {
        auto* casted = dynamic_cast<NumberExpression*>(node);
        if (!casted) {
            ADD_FAILURE() << "Expected Number expression '" << typeid(NumberExpression).name()
                          << "', got " << typeid(*node).name();
        }
        EXPECT_EQ(casted->getValue(), value);
    }
};

template <>
struct ASTChecker<BinaryExpression> {
    static BinaryExpression* check(ASTNode* node, TokenType OPtype) {
        auto* casted = dynamic_cast<BinaryExpression*>(node);
        if (!casted) {
            ADD_FAILURE() << "Expected Binary expression '" << typeid(BinaryExpression).name()
                          << "', got " << typeid(*node).name();
        }
        EXPECT_EQ(casted->getOP(), OPtype);
        return casted;
    }
};

template <>
struct ASTChecker<UnaryExpression> {
    static UnaryExpression* check(ASTNode* node, bool negative) {
        auto* casted = dynamic_cast<UnaryExpression*>(node);
        if (!casted) {
            ADD_FAILURE() << "Expected Unary expression '" << typeid(UnaryExpression).name()
                          << "', got " << typeid(*node).name();
        }
        EXPECT_EQ(casted->isNegative(), negative);
        return casted;
    }
};

inline void checkTokenVector(std::vector<Token> const& tokens,
                             std::vector<Token> const& correct_tokens) {
    ASSERT_EQ(tokens.size(), correct_tokens.size());
    for (size_t i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(tokens[i].text_, correct_tokens[i].text_);
        EXPECT_EQ(tokens[i].type_, correct_tokens[i].type_);
        EXPECT_EQ(tokens[i].position_, correct_tokens[i].position_);
    }
}
#endif
