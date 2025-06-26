#include <gtest/gtest.h>

#include "../../src/parser/parser.h"
#include "../util/testsUtil.h"

TEST(ParserTest, basic) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},      {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "3", {0, 2}},      {TokenType::SEMICOL, ";", {0, 3}},
        {TokenType::VAR, "b", {1, 0}},      {TokenType::ASSIGNMENT, "=", {1, 1}},
        {TokenType::INT, "4", {1, 2}},      {TokenType::SEMICOL, ";", {1, 3}},
        {TokenType::VAR, "c", {2, 0}},      {TokenType::ASSIGNMENT, "=", {2, 1}},
        {TokenType::VAR, "a", {2, 2}},      {TokenType::PLUS, "+", {2, 3}},
        {TokenType::VAR, "b", {2, 4}},      {TokenType::SEMICOL, ";", {2, 5}},
        {TokenType::ENDFILE, "EOF", {3, 0}}};
    Parser p(tokens);
    auto ast = p.Parse();
    ASSERT_EQ(ast.size(), 3);
    {  // statement: a=3;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[0].get(), "a");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 3);
    }

    {  // statement: b=4;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[1].get(), "b");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 4);
    }

    {  // statement: c=a+b;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[2].get(), "c");

        auto* expression =
            ASTChecker<BinaryExpression>::Check(statement->GetExpression().get(), TokenType::PLUS);
        ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(), "a");
        ASTChecker<VariableExpression>::Check(expression->GetRightExpression().get(), "b");
    }
}

TEST(ParserTest, factorial) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "res", {0, 0}},      {TokenType::ASSIGNMENT, "=", {0, 3}},
        {TokenType::INT, "1", {0, 4}},        {TokenType::SEMICOL, ";", {0, 5}},
        {TokenType::VAR, "n", {0, 7}},        {TokenType::ASSIGNMENT, "=", {0, 8}},
        {TokenType::INT, "6", {0, 9}},        {TokenType::SEMICOL, ";", {0, 10}},
        {TokenType::WHILE, "while", {1, 0}},  {TokenType::VAR, "n", {1, 6}},
        {TokenType::MORE, ">", {1, 7}},       {TokenType::INT, "1", {1, 8}},
        {TokenType::DO, "do", {1, 10}},       {TokenType::VAR, "res", {2, 4}},
        {TokenType::ASSIGNMENT, "=", {2, 7}}, {TokenType::VAR, "res", {2, 8}},
        {TokenType::MULTIPLY, "*", {2, 11}},  {TokenType::VAR, "n", {2, 12}},
        {TokenType::SEMICOL, ";", {2, 13}},   {TokenType::VAR, "n", {3, 4}},
        {TokenType::ASSIGNMENT, "=", {3, 5}}, {TokenType::VAR, "n", {3, 6}},
        {TokenType::MINUS, "-", {3, 7}},      {TokenType::INT, "1", {3, 8}},
        {TokenType::SEMICOL, ";", {3, 9}},    {TokenType::DONE, "done", {4, 0}},
        {TokenType::ENDFILE, "EOF", {5, 0}}};
    Parser p(tokens);
    auto ast = p.Parse();
    EXPECT_EQ(ast.size(), 3);
    {  // statement: res=1;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[0].get(), "res");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 1);
    }

    {  // statement: n=6;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[1].get(), "n");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 6);
    }

    {  // statement: while
        auto* statement = ASTChecker<WhileStatement>::Check(ast[2].get());
        {  // condition expression: n>1
            auto* condition = ASTChecker<BinaryExpression>::Check(statement->GetCondition().get(),
                                                                  TokenType::MORE);
            ASTChecker<VariableExpression>::Check(condition->GetLeftExpression().get(), "n");
            ASTChecker<NumberExpression>::Check(condition->GetRightExpression().get(), 1);
        }
        {  // body
            auto const& body = statement->GetBody();
            EXPECT_EQ(body.size(), 2);
            {  // body statement: res=res*n;
                auto* body_statement = ASTChecker<AssignmentStatement>::Check(body[0].get(), "res");

                auto* expression = ASTChecker<BinaryExpression>::Check(
                    body_statement->GetExpression().get(), TokenType::MULTIPLY);
                ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(), "res");
                ASTChecker<VariableExpression>::Check(expression->GetRightExpression().get(), "n");
            }

            {  // body statement: n=n-1;
                auto* body_statement = ASTChecker<AssignmentStatement>::Check(body[1].get(), "n");

                auto* expression = ASTChecker<BinaryExpression>::Check(
                    body_statement->GetExpression().get(), TokenType::MINUS);
                ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(), "n");
                ASTChecker<NumberExpression>::Check(expression->GetRightExpression().get(), 1);
            }
        }
    }
}

TEST(ParserTest, fibonacci) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "0", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
        {TokenType::VAR, "b", {0, 5}},        {TokenType::ASSIGNMENT, "=", {0, 6}},
        {TokenType::INT, "1", {0, 7}},        {TokenType::SEMICOL, ";", {0, 8}},
        {TokenType::VAR, "n", {0, 10}},       {TokenType::ASSIGNMENT, "=", {0, 11}},
        {TokenType::INT, "5", {0, 12}},       {TokenType::SEMICOL, ";", {0, 13}},
        {TokenType::WHILE, "while", {1, 0}},  {TokenType::VAR, "n", {1, 6}},
        {TokenType::MORE, ">", {1, 7}},       {TokenType::INT, "1", {1, 8}},
        {TokenType::DO, "do", {1, 10}},       {TokenType::VAR, "b", {2, 4}},
        {TokenType::ASSIGNMENT, "=", {2, 5}}, {TokenType::VAR, "a", {2, 6}},
        {TokenType::PLUS, "+", {2, 7}},       {TokenType::VAR, "b", {2, 8}},
        {TokenType::SEMICOL, ";", {2, 9}},    {TokenType::VAR, "a", {3, 4}},
        {TokenType::ASSIGNMENT, "=", {3, 5}}, {TokenType::VAR, "b", {3, 6}},
        {TokenType::MINUS, "-", {3, 7}},      {TokenType::VAR, "a", {3, 8}},
        {TokenType::SEMICOL, ";", {3, 9}},    {TokenType::VAR, "n", {4, 4}},
        {TokenType::ASSIGNMENT, "=", {4, 5}}, {TokenType::VAR, "n", {4, 6}},
        {TokenType::MINUS, "-", {4, 7}},      {TokenType::INT, "1", {4, 8}},
        {TokenType::SEMICOL, ";", {4, 9}},    {TokenType::DONE, "done", {5, 0}},
        {TokenType::ENDFILE, "EOF", {6, 0}}};
    Parser p(tokens);
    auto ast = p.Parse();
    EXPECT_EQ(ast.size(), 4);
    {  // statement: a=0;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[0].get(), "a");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 0);
    }

    {  // statement: b=1;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[1].get(), "b");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 1);
    }

    {  // statement: n=5;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[2].get(), "n");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 5);
    }

    {  // statement: while
        auto* statement = ASTChecker<WhileStatement>::Check(ast[3].get());
        {  // condition expression: n>1
            auto* condition = ASTChecker<BinaryExpression>::Check(statement->GetCondition().get(),
                                                                  TokenType::MORE);
            ASTChecker<VariableExpression>::Check(condition->GetLeftExpression().get(), "n");
            ASTChecker<NumberExpression>::Check(condition->GetRightExpression().get(), 1);
        }
        {  // body
            auto const& body = statement->GetBody();
            EXPECT_EQ(body.size(), 3);
            {  // body statement: b=a+b;
                auto* body_statement = ASTChecker<AssignmentStatement>::Check(body[0].get(), "b");

                auto* expression = ASTChecker<BinaryExpression>::Check(
                    body_statement->GetExpression().get(), TokenType::PLUS);
                ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(), "a");
                ASTChecker<VariableExpression>::Check(expression->GetRightExpression().get(), "b");
            }

            {  // body statement: a=b-a;
                auto* body_statement = ASTChecker<AssignmentStatement>::Check(body[1].get(), "a");

                auto* expression = ASTChecker<BinaryExpression>::Check(
                    body_statement->GetExpression().get(), TokenType::MINUS);
                ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(), "b");
                ASTChecker<VariableExpression>::Check(expression->GetRightExpression().get(), "a");
            }

            {  // body statement: n=n-1;
                auto* body_statement = ASTChecker<AssignmentStatement>::Check(body[2].get(), "n");

                auto* expression = ASTChecker<BinaryExpression>::Check(
                    body_statement->GetExpression().get(), TokenType::MINUS);
                ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(), "n");
                ASTChecker<NumberExpression>::Check(expression->GetRightExpression().get(), 1);
            }
        }
    }
}

TEST(ParserTest, arithmeticExpression) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "expression", {0, 0}}, {TokenType::ASSIGNMENT, "=", {0, 11}},
        {TokenType::LPAREN, "(", {0, 13}},      {TokenType::INT, "5", {0, 14}},
        {TokenType::PLUS, "+", {0, 16}},        {TokenType::INT, "3", {0, 18}},
        {TokenType::MULTIPLY, "*", {0, 20}},    {TokenType::MINUS, "-", {0, 22}},
        {TokenType::INT, "2", {0, 23}},         {TokenType::RPAREN, ")", {0, 24}},
        {TokenType::DIVIDE, "/", {0, 26}},      {TokenType::LPAREN, "(", {0, 28}},
        {TokenType::INT, "4", {0, 29}},         {TokenType::MINUS, "-", {0, 31}},
        {TokenType::INT, "1", {0, 33}},         {TokenType::RPAREN, ")", {0, 34}},
        {TokenType::SEMICOL, ";", {0, 35}},     {TokenType::ENDFILE, "EOF", {1, 0}}};

    Parser p(tokens);

    auto ast = p.Parse();
    ASSERT_EQ(ast.size(), 1);

    auto* statement = ASTChecker<AssignmentStatement>::Check(ast[0].get(), "expression");

    // full expression
    auto* expression =
        ASTChecker<BinaryExpression>::Check(statement->GetExpression().get(), TokenType::DIVIDE);

    auto* left =
        ASTChecker<BinaryExpression>::Check(expression->GetLeftExpression().get(), TokenType::PLUS);
    {
        ASTChecker<NumberExpression>::Check(left->GetLeftExpression().get(), 5);

        auto* inner_right = ASTChecker<BinaryExpression>::Check(left->GetRightExpression().get(),
                                                                TokenType::MULTIPLY);
        ASTChecker<NumberExpression>::Check(inner_right->GetLeftExpression().get(), 3);

        auto* inner_right_right =
            ASTChecker<UnaryExpression>::Check(inner_right->GetRightExpression().get(), true);
        ASTChecker<NumberExpression>::Check(inner_right_right->GetExpression().get(), 2);
    }

    auto* right = ASTChecker<BinaryExpression>::Check(expression->GetRightExpression().get(),
                                                      TokenType::MINUS);
    {
        ASTChecker<NumberExpression>::Check(right->GetLeftExpression().get(), 4);
        ASTChecker<NumberExpression>::Check(right->GetRightExpression().get(), 1);
    }
}

TEST(ParserTest, nestedIf) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "n", {0, 0}},      {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "10", {0, 2}},     {TokenType::SEMICOL, ";", {0, 4}},
        {TokenType::VAR, "flag", {1, 0}},   {TokenType::ASSIGNMENT, "=", {1, 4}},
        {TokenType::INT, "0", {1, 5}},      {TokenType::SEMICOL, ";", {1, 6}},
        {TokenType::IF, "if", {2, 0}},      {TokenType::VAR, "n", {2, 3}},
        {TokenType::MORE, ">", {2, 4}},     {TokenType::INT, "5", {2, 5}},
        {TokenType::THEN, "then", {2, 7}},  {TokenType::IF, "if", {3, 4}},
        {TokenType::VAR, "n", {3, 7}},      {TokenType::LESS, "<", {3, 8}},
        {TokenType::INT, "15", {3, 9}},     {TokenType::THEN, "then", {3, 12}},
        {TokenType::VAR, "flag", {4, 8}},   {TokenType::ASSIGNMENT, "=", {4, 12}},
        {TokenType::INT, "1", {4, 13}},     {TokenType::SEMICOL, ";", {4, 14}},
        {TokenType::FI, "fi", {5, 4}},      {TokenType::FI, "fi", {6, 0}},
        {TokenType::ENDFILE, "EOF", {7, 0}}};
    Parser p(tokens);
    auto ast = p.Parse();
    EXPECT_EQ(ast.size(), 3);

    {  // statement: n=10;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[0].get(), "n");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 10);
    }

    {  // statement: flag = 0;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[1].get(), "flag");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 0);
    }

    {  // statement: if-statement
        auto* statement = ASTChecker<IfStatement>::Check(ast[2].get());

        {  // condition expression: n>5
            auto* condition = ASTChecker<BinaryExpression>::Check(statement->GetCondition().get(),
                                                                  TokenType::MORE);
            ASTChecker<VariableExpression>::Check(condition->GetLeftExpression().get(), "n");
            ASTChecker<NumberExpression>::Check(condition->GetRightExpression().get(), 5);
        }

        {  // body
            auto const& body = statement->GetBody();
            EXPECT_EQ(body.size(), 1);
            {  // body statement: if-statement(nested)
                auto* body_statement = ASTChecker<IfStatement>::Check(body[0].get());
                {  // condition expression: n<15
                    auto* condition = ASTChecker<BinaryExpression>::Check(
                        body_statement->GetCondition().get(), TokenType::LESS);
                    ASTChecker<VariableExpression>::Check(condition->GetLeftExpression().get(),
                                                          "n");
                    ASTChecker<NumberExpression>::Check(condition->GetRightExpression().get(), 15);
                }

                {  // nested body statement: flag=1;
                    auto* nestedbody_statement = ASTChecker<AssignmentStatement>::Check(
                        body_statement->GetBody()[0].get(), "flag");
                    ASTChecker<NumberExpression>::Check(nestedbody_statement->GetExpression().get(),
                                                        1);
                }
            }
        }
    }
}

TEST(ParserTest, nestedWhile) {
    std::vector<Token> tokens = {
        {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
        {TokenType::INT, "0", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
        {TokenType::VAR, "b", {1, 0}},        {TokenType::ASSIGNMENT, "=", {1, 1}},
        {TokenType::INT, "0", {1, 2}},        {TokenType::SEMICOL, ";", {1, 3}},
        {TokenType::WHILE, "while", {2, 0}},  {TokenType::VAR, "a", {2, 6}},
        {TokenType::LESS, "<", {2, 7}},       {TokenType::INT, "2", {2, 8}},
        {TokenType::DO, "do", {2, 10}},       {TokenType::VAR, "c", {3, 4}},
        {TokenType::ASSIGNMENT, "=", {3, 5}}, {TokenType::INT, "0", {3, 6}},
        {TokenType::SEMICOL, ";", {3, 7}},    {TokenType::WHILE, "while", {4, 4}},
        {TokenType::VAR, "c", {4, 10}},       {TokenType::LESS, "<", {4, 11}},
        {TokenType::INT, "3", {4, 12}},       {TokenType::DO, "do", {4, 14}},
        {TokenType::VAR, "c", {5, 8}},        {TokenType::ASSIGNMENT, "=", {5, 9}},
        {TokenType::VAR, "c", {5, 10}},       {TokenType::PLUS, "+", {5, 11}},
        {TokenType::INT, "1", {5, 12}},       {TokenType::SEMICOL, ";", {5, 13}},
        {TokenType::VAR, "b", {6, 8}},        {TokenType::ASSIGNMENT, "=", {6, 9}},
        {TokenType::VAR, "b", {6, 10}},       {TokenType::PLUS, "+", {6, 11}},
        {TokenType::INT, "1", {6, 12}},       {TokenType::SEMICOL, ";", {6, 13}},
        {TokenType::DONE, "done", {7, 4}},    {TokenType::VAR, "a", {8, 4}},
        {TokenType::ASSIGNMENT, "=", {8, 5}}, {TokenType::VAR, "a", {8, 6}},
        {TokenType::PLUS, "+", {8, 7}},       {TokenType::INT, "1", {8, 8}},
        {TokenType::SEMICOL, ";", {8, 9}},    {TokenType::DONE, "done", {9, 0}},
        {TokenType::ENDFILE, "EOF", {10, 0}}};
    Parser p(tokens);
    auto ast = p.Parse();
    EXPECT_EQ(ast.size(), 3);

    {  // statement: a=0;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[0].get(), "a");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 0);
    }

    {  // statement: b=0;
        auto* statement = ASTChecker<AssignmentStatement>::Check(ast[1].get(), "b");
        ASTChecker<NumberExpression>::Check(statement->GetExpression().get(), 0);
    }

    {  // statement: while-statement
        auto* statement = ASTChecker<WhileStatement>::Check(ast[2].get());
        {  // condition expression: a<2
            auto* condition = ASTChecker<BinaryExpression>::Check(statement->GetCondition().get(),
                                                                  TokenType::LESS);
            ASTChecker<VariableExpression>::Check(condition->GetLeftExpression().get(), "a");
            ASTChecker<NumberExpression>::Check(condition->GetRightExpression().get(), 2);
        }

        {  // body
            auto const& body = statement->GetBody();
            EXPECT_EQ(body.size(), 3);
            {  // body statement: c=0;
                auto* body_statement = ASTChecker<AssignmentStatement>::Check(body[0].get(), "c");
                ASTChecker<NumberExpression>::Check(body_statement->GetExpression().get(), 0);
            }

            {  // body statement: while-statement(nested)
                auto* body_statement = ASTChecker<WhileStatement>::Check(body[1].get());
                {  // condition expression: c<3
                    auto* condition = ASTChecker<BinaryExpression>::Check(
                        body_statement->GetCondition().get(), TokenType::LESS);
                    ASTChecker<VariableExpression>::Check(condition->GetLeftExpression().get(),
                                                          "c");
                    ASTChecker<NumberExpression>::Check(condition->GetRightExpression().get(), 3);
                }

                {  // nested body statement: c=c+1;
                    auto* nestedbody_statement = ASTChecker<AssignmentStatement>::Check(
                        body_statement->GetBody()[0].get(), "c");

                    auto* expression = ASTChecker<BinaryExpression>::Check(
                        nestedbody_statement->GetExpression().get(), TokenType::PLUS);
                    ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(),
                                                          "c");
                    ASTChecker<NumberExpression>::Check(expression->GetRightExpression().get(), 1);
                }

                {  // nested body statement: b=b+1;
                    auto* nestedbody_statement = ASTChecker<AssignmentStatement>::Check(
                        body_statement->GetBody()[1].get(), "b");

                    auto* expression = ASTChecker<BinaryExpression>::Check(
                        nestedbody_statement->GetExpression().get(), TokenType::PLUS);
                    ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(),
                                                          "b");
                    ASTChecker<NumberExpression>::Check(expression->GetRightExpression().get(), 1);
                }
            }

            {  // body statement: a=a+1;
                auto* body_statement = ASTChecker<AssignmentStatement>::Check(body[2].get(), "a");

                auto* expression = ASTChecker<BinaryExpression>::Check(
                    body_statement->GetExpression().get(), TokenType::PLUS);
                ASTChecker<VariableExpression>::Check(expression->GetLeftExpression().get(), "a");
                ASTChecker<NumberExpression>::Check(expression->GetRightExpression().get(), 1);
            }
        }
    }
}
