#include "../code-generation/codegenerator.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"

class Compiler {
public:
    explicit Compiler(CompilerConfig& config) : config_(config){};

    std::string Compile(std::string input_path) {
        Lexer lexer = Lexer(std::move(input_path));
        auto tokens = lexer.Tokenize();
        Parser parser = Parser(std::move(tokens));
        auto ast = parser.Parse();
        CodeGenerator generator = CodeGenerator(config_);
        return generator.Generate(ast);
    }

private:
    CompilerConfig config_;
};