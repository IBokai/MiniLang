#include <gtest/gtest.h>

#include "../../../src/AST/ASTNode.h"
#include "../../../src/AST/expressions.h"
#include "../../../src/AST/statements.h"
#include "../../../src/code-generation/generator-factory/factory.h"
#include "../../../src/exceptions/exceptions.h"
#include "../../../src/lexer/lexer.h"
#include "../../../src/parser/parser.h"

namespace tests::codegeneratortests {

using namespace compiler::ast;
using namespace compiler::lexer;
using namespace compiler::parser;
using namespace compiler::codegenerator;
using namespace compiler::exceptions;

TEST(CcodegeneratorExcpetionTest, notDeclaredVariable) {
    Lexer lexer("../samples/codegenErrors/not-declared-variable.mlang");
    auto tokens = lexer.Tokenize();
    Parser parser(tokens);
    auto ast = parser.Parse();
    auto formatting_config = compiler::configs::FormattingConfig();
    auto generator = CreateGenerator(compiler::configs::Language::C, formatting_config);
    try {
        generator->Generate(ast);
        FAIL() << "Expected to throw an exception";
    } catch (CompilerException const& e) {
        EXPECT_EQ(std::string(e.what()), "Code generation error: variable 'l' is not declared");
    }
}
}  // namespace tests::codegeneratortests