#include <gtest/gtest.h>

#include "../../../src/AST/ASTNode.h"
#include "../../../src/AST/expressions.h"
#include "../../../src/AST/statements.h"
#include "../../../src/code-generation/generator-factory/factory.h"
#include "../../../src/lexer/lexer.h"
#include "../../../src/parser/parser.h"

namespace tests::codegeneratortests {

using namespace compiler::ast;
using namespace compiler::lexer;
using namespace compiler::parser;
using namespace compiler::codegenerator;

TEST(CcodegeneratorTest, basic) {
    Lexer lexer("../samples/basic.mlang");
    auto tokens = lexer.Tokenize();
    Parser parser(tokens);
    auto ast = parser.Parse();
    auto formatting_config = compiler::configs::FormattingConfig();
    auto generator = CreateGenerator(compiler::configs::Language::C, formatting_config);
    std::string code = generator->Generate(ast);
    std::string correct_code;
    std::ifstream file("../tests/code-generator/C/correct-code/basic.txt");
    std::string line;
    while (std::getline(file, line)) {
        correct_code += line + '\n';
    }
    EXPECT_EQ(code, correct_code);
}

TEST(CcodegeneratorTest, arithmeticExpression) {
    Lexer lexer("../samples/arithmetic-expression.mlang");
    auto tokens = lexer.Tokenize();
    Parser parser(tokens);
    auto ast = parser.Parse();
    auto formatting_config = compiler::configs::FormattingConfig();
    auto generator = CreateGenerator(compiler::configs::Language::C, formatting_config);
    std::string code = generator->Generate(ast);
    std::string correct_code;
    std::ifstream file("../tests/code-generator/C/correct-code/arithmetic-expression.txt");
    std::string line;
    while (std::getline(file, line)) {
        correct_code += line + '\n';
    }
    EXPECT_EQ(code, correct_code);
}

TEST(CcodegeneratorTest, factorial) {
    Lexer lexer("../samples/factorial.mlang");
    auto tokens = lexer.Tokenize();
    Parser parser(tokens);
    auto ast = parser.Parse();
    auto formatting_config = compiler::configs::FormattingConfig();
    auto generator = CreateGenerator(compiler::configs::Language::C, formatting_config);
    std::string code = generator->Generate(ast);
    std::string correct_code;
    std::ifstream file("../tests/code-generator/C/correct-code/factorial.txt");
    std::string line;
    while (std::getline(file, line)) {
        correct_code += line + '\n';
    }
    EXPECT_EQ(code, correct_code);
}

TEST(CcodegeneratorTest, fibonacci) {
    Lexer lexer("../samples/fibonacci.mlang");
    auto tokens = lexer.Tokenize();
    Parser parser(tokens);
    auto ast = parser.Parse();
    auto formatting_config = compiler::configs::FormattingConfig();
    auto generator = CreateGenerator(compiler::configs::Language::C, formatting_config);
    std::string code = generator->Generate(ast);
    std::string correct_code;
    std::ifstream file("../tests/code-generator/C/correct-code/fibonacci.txt");
    std::string line;
    while (std::getline(file, line)) {
        correct_code += line + '\n';
    }
    EXPECT_EQ(code, correct_code);
}

TEST(CcodegeneratorTest, nestedIf) {
    Lexer lexer("../samples/nested-if.mlang");
    auto tokens = lexer.Tokenize();
    Parser parser(tokens);
    auto ast = parser.Parse();
    auto formatting_config = compiler::configs::FormattingConfig();
    auto generator = CreateGenerator(compiler::configs::Language::C, formatting_config);
    std::string code = generator->Generate(ast);
    std::string correct_code;
    std::ifstream file("../tests/code-generator/C/correct-code/nested-if.txt");
    std::string line;
    while (std::getline(file, line)) {
        correct_code += line + '\n';
    }
    EXPECT_EQ(code, correct_code);
}

TEST(CcodegeneratorTest, nestedWhile) {
    Lexer lexer("../samples/nested-while.mlang");
    auto tokens = lexer.Tokenize();
    Parser parser(tokens);
    auto ast = parser.Parse();
    auto formatting_config = compiler::configs::FormattingConfig();
    auto generator = CreateGenerator(compiler::configs::Language::C, formatting_config);
    std::string code = generator->Generate(ast);
    std::string correct_code;
    std::ifstream file("../tests/code-generator/C/correct-code/nested-while.txt");
    std::string line;
    while (std::getline(file, line)) {
        correct_code += line + '\n';
    }
    EXPECT_EQ(code, correct_code);
}

}  // namespace tests::codegeneratortests