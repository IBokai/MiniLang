#ifndef COMPILER_H
#define COMPILER_H

#include "../code-generation/generator-factory/factory.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"

namespace compiler {
class Compiler {
public:
    explicit Compiler(configs::CompilerConfig const& config) : config_(config){};

    void Compile(std::string const& input_path, std::string const& output_path) const {
        lexer::Lexer lexer(input_path);
        auto tokens = lexer.Tokenize();
        parser::Parser parser(std::move(tokens));
        auto ast = parser.Parse();
        auto formatting_config = configs::FormattingConfig();
        auto generator = codegenerator::CreateGenerator(config_.GetLanguage(), formatting_config);
        std::string code = generator->Generate(ast);
        std::ofstream output(output_path);
        output << code;
    }

private:
    configs::CompilerConfig config_;
};
}  // namespace compiler
#endif