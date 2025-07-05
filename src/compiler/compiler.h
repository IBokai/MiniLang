#include "../code-generation/codegenerator.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"

namespace compiler {
class Compiler {
public:
    explicit Compiler(configs::CompilerConfig& config) : config_(config){};

    void Compile(std::string const& input_path, std::string const& output_path) {
        lexer::Lexer lexer(input_path);
        auto tokens = lexer.Tokenize();
        parser::Parser parser(std::move(tokens));
        auto ast = parser.Parse();
        codegenerator::CodeGenerator generator(config_.GetLanguage());
        std::string code = generator.Generate(ast);
        std::ofstream output(output_path);
        if (!output) {
            throw std::runtime_error("Failed to open output file");
        }
        output << code;
    }

private:
    configs::CompilerConfig config_;
};
}  // namespace compiler