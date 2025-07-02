#include "../code-generation/codegenerator.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"

class Compiler {
public:
    explicit Compiler(CompilerConfig& config) : config_(config){};

    void Compile(std::string const& input_path, std::string const& output_path) {
        Lexer lexer(input_path);
        auto tokens = lexer.Tokenize();
        Parser parser(std::move(tokens));
        auto ast = parser.Parse();
        CodeGenerator generator = CodeGenerator(config_);
        std::string code = generator.Generate(ast);
        std::ofstream output(output_path);
        if (!output) {
            throw std::runtime_error("Failed to open output file");
        }
        output << code;
    }

private:
    CompilerConfig config_;
};