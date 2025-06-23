#include <gtest/gtest.h>

#include "../src/lexer/lexer.h"
#include "../src/parser/parser.h"

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
    auto AST = p.parse();
    ASSERT_EQ(AST.size(), 3);
    {  // statement: a=3;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[0].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "a");

        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        ASSERT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 3);
    }

    {  // statement: b=4;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[1].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "b");

        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        ASSERT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 4);
    }

    {  // statement: c=a+b;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[2].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "c");

        auto* expression = dynamic_cast<BinaryExpression*>(statement->getExpression().get());
        ASSERT_NE(expression, nullptr);
        EXPECT_EQ(expression->getOP(), TokenType::PLUS);

        auto* left = dynamic_cast<VariableExpression*>(expression->getLeftExpression().get());
        ASSERT_NE(left, nullptr);
        EXPECT_EQ(left->getName(), "a");

        auto* right = dynamic_cast<VariableExpression*>(expression->getRightExpression().get());
        ASSERT_NE(right, nullptr);
        EXPECT_EQ(right->getName(), "b");
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
    auto AST = p.parse();
    EXPECT_EQ(AST.size(), 3);
    {  // statement: res=1;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[0].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "res");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        EXPECT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 1);
    }

    {  // statement: n=6;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[1].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "n");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        EXPECT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 6);
    }

    {  // statement: while
        auto* statement = dynamic_cast<WhileStatement*>(AST[2].get());
        ASSERT_NE(statement, nullptr);
        {  // condition expression: n>1
            auto* condition = dynamic_cast<BinaryExpression*>(statement->getCondition().get());
            ASSERT_NE(condition, nullptr);
            EXPECT_EQ(condition->getOP(), TokenType::MORE);
            auto* left = dynamic_cast<VariableExpression*>(condition->getLeftExpression().get());
            ASSERT_NE(left, nullptr);
            EXPECT_EQ(left->getName(), "n");
            auto* right = dynamic_cast<NumberExpression*>(condition->getRightExpression().get());
            ASSERT_NE(right, nullptr);
            EXPECT_EQ(right->getValue(), 1);
        }
        {  // body
            auto const& body = statement->getBody();
            EXPECT_EQ(body.size(), 2);
            {  // body statement: res=res*n;
                auto* body_statement = dynamic_cast<AssignmentStatement*>(body[0].get());
                ASSERT_NE(body_statement, nullptr);
                EXPECT_EQ(body_statement->getName(), "res");
                auto* expression =
                        dynamic_cast<BinaryExpression*>(body_statement->getExpression().get());
                ASSERT_NE(expression, nullptr);
                EXPECT_EQ(expression->getOP(), TokenType::MULTIPLY);
                auto* left =
                        dynamic_cast<VariableExpression*>(expression->getLeftExpression().get());
                ASSERT_NE(left, nullptr);
                EXPECT_EQ(left->getName(), "res");
                auto* right =
                        dynamic_cast<VariableExpression*>(expression->getRightExpression().get());
                ASSERT_NE(right, nullptr);
                EXPECT_EQ(right->getName(), "n");
            }

            {  // body statement: n=n-1;
                auto* body_statement = dynamic_cast<AssignmentStatement*>(body[1].get());
                ASSERT_NE(body_statement, nullptr);
                EXPECT_EQ(body_statement->getName(), "n");
                auto* expression =
                        dynamic_cast<BinaryExpression*>(body_statement->getExpression().get());
                ASSERT_NE(expression, nullptr);
                EXPECT_EQ(expression->getOP(), TokenType::MINUS);
                auto* left =
                        dynamic_cast<VariableExpression*>(expression->getLeftExpression().get());
                ASSERT_NE(left, nullptr);
                EXPECT_EQ(left->getName(), "n");
                auto* right =
                        dynamic_cast<NumberExpression*>(expression->getRightExpression().get());
                ASSERT_NE(right, nullptr);
                EXPECT_EQ(right->getValue(), 1);
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
    auto AST = p.parse();
    EXPECT_EQ(AST.size(), 4);
    {  // statement: a=0;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[0].get());
        EXPECT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "a");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        EXPECT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 0);
    }

    {  // statement: b=1;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[1].get());
        EXPECT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "b");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        EXPECT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 1);
    }

    {  // statement: n=5;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[2].get());
        EXPECT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "n");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        EXPECT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 5);
    }

    {  // statement: while
        auto* statement = dynamic_cast<WhileStatement*>(AST[3].get());
        EXPECT_NE(statement, nullptr);
        {  // condition expression: n>1
            auto* condition = dynamic_cast<BinaryExpression*>(statement->getCondition().get());
            EXPECT_NE(condition, nullptr);
            EXPECT_EQ(condition->getOP(), TokenType::MORE);
            auto* left = dynamic_cast<VariableExpression*>(condition->getLeftExpression().get());
            EXPECT_NE(left, nullptr);
            EXPECT_EQ(left->getName(), "n");
            auto* right = dynamic_cast<NumberExpression*>(condition->getRightExpression().get());
            EXPECT_NE(right, nullptr);
            EXPECT_EQ(right->getValue(), 1);
        }
        {  // body
            auto const& body = statement->getBody();
            EXPECT_EQ(body.size(), 3);
            {  // body statement: b=a+b;
                auto* body_statement = dynamic_cast<AssignmentStatement*>(body[0].get());
                ASSERT_NE(body_statement, nullptr);
                EXPECT_EQ(body_statement->getName(), "b");
                auto* expression =
                        dynamic_cast<BinaryExpression*>(body_statement->getExpression().get());
                ASSERT_NE(expression, nullptr);
                EXPECT_EQ(expression->getOP(), TokenType::PLUS);
                auto* left =
                        dynamic_cast<VariableExpression*>(expression->getLeftExpression().get());
                ASSERT_NE(left, nullptr);
                EXPECT_EQ(left->getName(), "a");
                auto* right =
                        dynamic_cast<VariableExpression*>(expression->getRightExpression().get());
                ASSERT_NE(right, nullptr);
                EXPECT_EQ(right->getName(), "b");
            }

            {  // body statement: a=b-a;
                auto* body_statement = dynamic_cast<AssignmentStatement*>(body[1].get());
                ASSERT_NE(body_statement, nullptr);
                EXPECT_EQ(body_statement->getName(), "a");
                auto* expression =
                        dynamic_cast<BinaryExpression*>(body_statement->getExpression().get());
                ASSERT_NE(expression, nullptr);
                EXPECT_EQ(expression->getOP(), TokenType::MINUS);
                auto* left =
                        dynamic_cast<VariableExpression*>(expression->getLeftExpression().get());
                ASSERT_NE(left, nullptr);
                EXPECT_EQ(left->getName(), "b");
                auto* right =
                        dynamic_cast<VariableExpression*>(expression->getRightExpression().get());
                ASSERT_NE(right, nullptr);
                EXPECT_EQ(right->getName(), "a");
            }

            {  // body statement: n=n-1;
                auto* body_statement = dynamic_cast<AssignmentStatement*>(body[2].get());
                ASSERT_NE(body_statement, nullptr);
                EXPECT_EQ(body_statement->getName(), "n");
                auto* expression =
                        dynamic_cast<BinaryExpression*>(body_statement->getExpression().get());
                ASSERT_NE(expression, nullptr);
                EXPECT_EQ(expression->getOP(), TokenType::MINUS);
                auto* left =
                        dynamic_cast<VariableExpression*>(expression->getLeftExpression().get());
                ASSERT_NE(left, nullptr);
                EXPECT_EQ(left->getName(), "n");
                auto* right =
                        dynamic_cast<NumberExpression*>(expression->getRightExpression().get());
                ASSERT_NE(right, nullptr);
                EXPECT_EQ(right->getValue(), 1);
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

    auto AST = p.parse();
    ASSERT_EQ(AST.size(), 1);

    auto* statement = dynamic_cast<AssignmentStatement*>(AST[0].get());
    ASSERT_NE(statement, nullptr);
    EXPECT_EQ(statement->getName(), "expression");

    // full expression
    auto* expression = dynamic_cast<BinaryExpression*>(statement->getExpression().get());
    EXPECT_EQ(expression->getOP(), TokenType::DIVIDE);

    auto* left = dynamic_cast<BinaryExpression*>(expression->getLeftExpression().get());
    ASSERT_NE(left, nullptr);
    {
        auto* inner_left = dynamic_cast<NumberExpression*>(left->getLeftExpression().get());
        ASSERT_NE(inner_left, nullptr);
        EXPECT_EQ(inner_left->getValue(), 5);

        auto* inner_right = dynamic_cast<BinaryExpression*>(left->getRightExpression().get());
        ASSERT_NE(inner_right, nullptr);
        EXPECT_EQ(inner_right->getOP(), TokenType::MULTIPLY);
        auto* inner_right_left =
                dynamic_cast<NumberExpression*>(inner_right->getLeftExpression().get());
        ASSERT_NE(inner_right_left, nullptr);
        EXPECT_EQ(inner_right_left->getValue(), 3);
        auto* inner_right_right =
                dynamic_cast<UnaryExpression*>(inner_right->getRightExpression().get());
        ASSERT_NE(inner_right_right, nullptr);
        EXPECT_EQ(inner_right_right->isNegative(), true);
        auto* inner_right_right_primary =
                dynamic_cast<NumberExpression*>(inner_right_right->getExpression().get());
        ASSERT_NE(inner_right_right_primary, nullptr);
        EXPECT_EQ(inner_right_right_primary->getValue(), 2);
    }

    auto* right = dynamic_cast<BinaryExpression*>(expression->getRightExpression().get());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->getOP(), TokenType::MINUS);
    {
        auto* inner_left = dynamic_cast<NumberExpression*>(right->getLeftExpression().get());
        ASSERT_NE(inner_left, nullptr);
        EXPECT_EQ(inner_left->getValue(), 4);

        auto* inner_right = dynamic_cast<NumberExpression*>(right->getRightExpression().get());
        ASSERT_NE(inner_right, nullptr);
        EXPECT_EQ(inner_right->getValue(), 1);
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
    auto AST = p.parse();
    EXPECT_EQ(AST.size(), 3);

    {  // statement: n=10;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[0].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "n");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        ASSERT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 10);
    }

    {  // statement: flag = 0;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[1].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "flag");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        ASSERT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 0);
    }

    {  // statement: if-statement
        auto* statement = dynamic_cast<IfStatement*>(AST[2].get());
        ASSERT_NE(statement, nullptr);
        {  // condition expression: n>5
            auto* condition = dynamic_cast<BinaryExpression*>(statement->getCondition().get());
            ASSERT_NE(condition, nullptr);
            ASSERT_EQ(condition->getOP(), TokenType::MORE);
            auto* left = dynamic_cast<VariableExpression*>(condition->getLeftExpression().get());
            ASSERT_NE(left, nullptr);
            EXPECT_EQ(left->getName(), "n");
            auto* right = dynamic_cast<NumberExpression*>(condition->getRightExpression().get());
            ASSERT_NE(right, nullptr);
            EXPECT_EQ(right->getValue(), 5);
        }

        {  // body
            auto const& body = statement->getBody();
            EXPECT_EQ(body.size(), 1);
            {  // body statment: if-statement(nested)
                auto* bodyStatement = dynamic_cast<IfStatement*>(body[0].get());
                ASSERT_NE(bodyStatement, nullptr);
                {  // condition expression: n<15
                    auto* condition =
                            dynamic_cast<BinaryExpression*>(bodyStatement->getCondition().get());
                    ASSERT_NE(condition, nullptr);
                    EXPECT_EQ(condition->getOP(), TokenType::LESS);
                    auto* left =
                            dynamic_cast<VariableExpression*>(condition->getLeftExpression().get());
                    ASSERT_NE(left, nullptr);
                    EXPECT_EQ(left->getName(), "n");
                    auto* right =
                            dynamic_cast<NumberExpression*>(condition->getRightExpression().get());
                    ASSERT_NE(right, nullptr);
                    EXPECT_EQ(right->getValue(), 15);
                }

                {  // nested body statement: flag=1;
                    auto* nestedbodyStatement =
                            dynamic_cast<AssignmentStatement*>(bodyStatement->getBody()[0].get());
                    ASSERT_NE(nestedbodyStatement, nullptr);
                    EXPECT_EQ(nestedbodyStatement->getName(), "flag");
                    auto* expression = dynamic_cast<NumberExpression*>(
                            nestedbodyStatement->getExpression().get());
                    ASSERT_NE(expression, nullptr);
                    EXPECT_EQ(expression->getValue(), 1);
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
    auto AST = p.parse();
    EXPECT_EQ(AST.size(), 3);

    {  // statement: a=0;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[0].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "a");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        ASSERT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 0);
    }

    {  // statement: b=0;
        auto* statement = dynamic_cast<AssignmentStatement*>(AST[1].get());
        ASSERT_NE(statement, nullptr);
        EXPECT_EQ(statement->getName(), "b");
        auto* expression = dynamic_cast<NumberExpression*>(statement->getExpression().get());
        ASSERT_NE(expression, nullptr);
        EXPECT_EQ(expression->getValue(), 0);
    }

    {  // statement: while-statement
        auto* statement = dynamic_cast<WhileStatement*>(AST[2].get());
        ASSERT_NE(statement, nullptr);
        {  // condition expression: a<2
            auto* condition = dynamic_cast<BinaryExpression*>(statement->getCondition().get());
            ASSERT_NE(condition, nullptr);
            ASSERT_EQ(condition->getOP(), TokenType::LESS);
            auto* left = dynamic_cast<VariableExpression*>(condition->getLeftExpression().get());
            ASSERT_NE(left, nullptr);
            EXPECT_EQ(left->getName(), "a");
            auto* right = dynamic_cast<NumberExpression*>(condition->getRightExpression().get());
            ASSERT_NE(right, nullptr);
            EXPECT_EQ(right->getValue(), 2);
        }

        {  // body
            auto const& body = statement->getBody();
            EXPECT_EQ(body.size(), 3);
            {  // body statement: c=0;
                auto* bodyStatement = dynamic_cast<AssignmentStatement*>(body[0].get());
                ASSERT_NE(bodyStatement, nullptr);
                EXPECT_EQ(bodyStatement->getName(), "c");
                auto* expression =
                        dynamic_cast<NumberExpression*>(bodyStatement->getExpression().get());
                ASSERT_NE(expression, nullptr);
                EXPECT_EQ(expression->getValue(), 0);
            }

            {  // body statment: while-statement(nested)
                auto* bodyStatement = dynamic_cast<WhileStatement*>(body[1].get());
                ASSERT_NE(bodyStatement, nullptr);
                {  // condition expression: c<3
                    auto* condition =
                            dynamic_cast<BinaryExpression*>(bodyStatement->getCondition().get());
                    ASSERT_NE(condition, nullptr);
                    EXPECT_EQ(condition->getOP(), TokenType::LESS);
                    auto* left =
                            dynamic_cast<VariableExpression*>(condition->getLeftExpression().get());
                    ASSERT_NE(left, nullptr);
                    EXPECT_EQ(left->getName(), "c");
                    auto* right =
                            dynamic_cast<NumberExpression*>(condition->getRightExpression().get());
                    ASSERT_NE(right, nullptr);
                    EXPECT_EQ(right->getValue(), 3);
                }

                {  // nested body statement: c=c+1;
                    auto* nestedbodyStatement =
                            dynamic_cast<AssignmentStatement*>(bodyStatement->getBody()[0].get());
                    ASSERT_NE(nestedbodyStatement, nullptr);
                    EXPECT_EQ(nestedbodyStatement->getName(), "c");
                    auto* expression = dynamic_cast<BinaryExpression*>(
                            nestedbodyStatement->getExpression().get());
                    ASSERT_NE(expression, nullptr);
                    EXPECT_EQ(expression->getOP(), TokenType::PLUS);
                    auto* left = dynamic_cast<VariableExpression*>(
                            expression->getLeftExpression().get());
                    ASSERT_NE(left, nullptr);
                    EXPECT_EQ(left->getName(), "c");
                    auto* right =
                            dynamic_cast<NumberExpression*>(expression->getRightExpression().get());
                    ASSERT_NE(right, nullptr);
                    EXPECT_EQ(right->getValue(), 1);
                }

                {  // nested body statement: b=b+1;
                    auto* nestedbodyStatement =
                            dynamic_cast<AssignmentStatement*>(bodyStatement->getBody()[1].get());
                    ASSERT_NE(nestedbodyStatement, nullptr);
                    EXPECT_EQ(nestedbodyStatement->getName(), "b");
                    auto* expression = dynamic_cast<BinaryExpression*>(
                            nestedbodyStatement->getExpression().get());
                    ASSERT_NE(expression, nullptr);
                    EXPECT_EQ(expression->getOP(), TokenType::PLUS);
                    auto* left = dynamic_cast<VariableExpression*>(
                            expression->getLeftExpression().get());
                    ASSERT_NE(left, nullptr);
                    EXPECT_EQ(left->getName(), "b");
                    auto* right =
                            dynamic_cast<NumberExpression*>(expression->getRightExpression().get());
                    ASSERT_NE(right, nullptr);
                    EXPECT_EQ(right->getValue(), 1);
                }
            }

            {  // body statement: a=a+1;
                auto* bodyStatement = dynamic_cast<AssignmentStatement*>(body[2].get());
                ASSERT_NE(bodyStatement, nullptr);
                EXPECT_EQ(bodyStatement->getName(), "a");
                auto* expression =
                        dynamic_cast<BinaryExpression*>(bodyStatement->getExpression().get());
                ASSERT_NE(expression, nullptr);
                EXPECT_EQ(expression->getOP(), TokenType::PLUS);
                auto* left =
                        dynamic_cast<VariableExpression*>(expression->getLeftExpression().get());
                ASSERT_NE(left, nullptr);
                EXPECT_EQ(left->getName(), "a");
                auto* right =
                        dynamic_cast<NumberExpression*>(expression->getRightExpression().get());
                ASSERT_NE(right, nullptr);
                EXPECT_EQ(right->getValue(), 1);
            }
        }
    }
}

TEST(ParserTest, noSemicolon) {
    std::vector<Token> tokens = {
            {TokenType::VAR, "num", {0, 0}}, {TokenType::ASSIGNMENT, "=", {0, 4}},
            {TokenType::INT, "2", {0, 6}},   {TokenType::PLUS, "+", {0, 8}},
            {TokenType::INT, "2", {0, 10}},  {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected semicolon after assignment statement");
    }
}

TEST(ParserTest, noStatement) {
    std::vector<Token> tokens = {{TokenType::INT, "2", {0, 0}},
                                 {TokenType::PLUS, "+", {0, 1}},
                                 {TokenType::INT, "3", {0, 2}},
                                 {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected statement");
    }
}

TEST(ParserTest, noAssign) {
    std::vector<Token> tokens = {{TokenType::VAR, "a", {0, 0}},
                                 {TokenType::INT, "3", {0, 2}},
                                 {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected assignment sign after variable name");
    }
}

TEST(ParserTest, noThen) {
    std::vector<Token> tokens = {
            {TokenType::VAR, "a", {0, 0}},  {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "3", {0, 2}},  {TokenType::SEMICOL, ";", {0, 3}},
            {TokenType::IF, "if", {1, 0}},  {TokenType::VAR, "a", {1, 3}},
            {TokenType::LESS, "<", {1, 4}}, {TokenType::INT, "5", {1, 5}},
            {TokenType::VAR, "a", {2, 4}},  {TokenType::ASSIGNMENT, "=", {2, 5}},
            {TokenType::VAR, "a", {2, 6}},  {TokenType::MULTIPLY, "*", {2, 7}},
            {TokenType::INT, "2", {2, 8}},  {TokenType::SEMICOL, ";", {2, 9}},
            {TokenType::FI, "fi", {3, 0}},  {TokenType::ENDFILE, "EOF", {4, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Expected then keyword after condition expression in if statement");
    }
}

TEST(ParserTest, noFi) {
    std::vector<Token> tokens = {
            {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "3", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
            {TokenType::IF, "if", {1, 0}},        {TokenType::VAR, "a", {1, 3}},
            {TokenType::LESS, "<", {1, 4}},       {TokenType::INT, "5", {1, 5}},
            {TokenType::THEN, "then", {1, 7}},    {TokenType::VAR, "a", {2, 4}},
            {TokenType::ASSIGNMENT, "=", {2, 5}}, {TokenType::VAR, "a", {2, 6}},
            {TokenType::MULTIPLY, "*", {2, 7}},   {TokenType::INT, "2", {2, 8}},
            {TokenType::SEMICOL, ";", {2, 9}},    {TokenType::ENDFILE, "EOF", {3, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected fi keyword before the end of the program");
    }
}

TEST(ParserTest, noDo) {
    std::vector<Token> tokens = {
            {TokenType::VAR, "a", {0, 0}},       {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "3", {0, 2}},       {TokenType::SEMICOL, ";", {0, 3}},
            {TokenType::WHILE, "while", {1, 0}}, {TokenType::VAR, "a", {1, 6}},
            {TokenType::MORE, ">", {1, 7}},      {TokenType::INT, "0", {1, 8}},
            {TokenType::VAR, "a", {2, 4}},       {TokenType::ASSIGNMENT, "=", {2, 5}},
            {TokenType::VAR, "a", {2, 6}},       {TokenType::MINUS, "-", {2, 7}},
            {TokenType::INT, "1", {2, 8}},       {TokenType::SEMICOL, ";", {2, 9}},
            {TokenType::DONE, "done", {3, 0}},   {TokenType::ENDFILE, "EOF", {4, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()),
                  "Expected do keyword after condition epxression in while statement");
    }
}

TEST(ParserTest, noDone) {
    std::vector<Token> tokens = {
            {TokenType::VAR, "a", {0, 0}},        {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "3", {0, 2}},        {TokenType::SEMICOL, ";", {0, 3}},
            {TokenType::WHILE, "while", {1, 0}},  {TokenType::VAR, "a", {1, 6}},
            {TokenType::MORE, ">", {1, 7}},       {TokenType::INT, "0", {1, 8}},
            {TokenType::DO, "do", {1, 10}},       {TokenType::VAR, "a", {2, 4}},
            {TokenType::ASSIGNMENT, "=", {2, 5}}, {TokenType::VAR, "a", {2, 6}},
            {TokenType::MINUS, "-", {2, 7}},      {TokenType::INT, "1", {2, 8}},
            {TokenType::SEMICOL, ";", {2, 9}},    {TokenType::ENDFILE, "EOF", {3, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected done keyword before the end of the program");
    }
}

TEST(ParserTest, unexpectedToken) {
    std::vector<Token> tokens = {
            {TokenType::VAR, "a", {0, 0}},       {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "2", {0, 2}},       {TokenType::PLUS, "+", {0, 3}},
            {TokenType::INT, "2", {0, 4}},       {TokenType::PLUS, "+", {0, 5}},
            {TokenType::WHILE, "while", {0, 6}}, {TokenType::SEMICOL, ";", {0, 11}},
            {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected number, variable or '('");
    }
}

TEST(ParserTest, noClosingParenthesis) {
    std::vector<Token> tokens = {
            {TokenType::VAR, "a", {0, 0}},     {TokenType::ASSIGNMENT, "=", {0, 1}},
            {TokenType::INT, "2", {0, 2}},     {TokenType::MULTIPLY, "*", {0, 3}},
            {TokenType::LPAREN, "(", {0, 4}},  {TokenType::INT, "2", {0, 5}},
            {TokenType::PLUS, "+", {0, 6}},    {TokenType::INT, "2", {0, 7}},
            {TokenType::SEMICOL, ";", {0, 8}}, {TokenType::ENDFILE, "EOF", {1, 0}}};
    Parser p(tokens);
    try {
        p.parse();
        FAIL() << "Expected to throw an exception";
    } catch (const std::exception& e) {
        EXPECT_EQ(std::string(e.what()), "Expected ')'");
    }
}