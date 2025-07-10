#include <iostream>
#include <regex>

#include "../configs/configs.h"
#include "../exceptions/exceptions.h"

namespace cliparser {

using namespace compiler::configs;
using namespace compiler::exceptions;

class CLIParser {
public:
    explicit CLIParser() {}

    std::tuple<std::string, std::string, CompilerConfig> Parse(char** argv, int argc) {
        // do not count ./main
        if (argc - 1 > 3) {
            throw CliParserException("Too many arguments: expected 2 or 3 arguments");
        }
        if (argc - 1 < 2) {
            throw CliParserException("Too few arguments: expected 2 or 3 arguments");
        }
        if (!CheckOption(argv[1], std::regex("^.*\\.mlang$"))) {
            throw CliParserException(
                "Invalid input file: incorrect format, expected .mlang format");
        }
        if (!CheckOption(argv[2], std::regex("^.*\\.(c|s|txt)$"))) {
            throw CliParserException(
                "Invalid output file: incorrect format, expected .c|.s|.txt formats");
        }
        if (argc - 1 != 3) {
            return {argv[1], argv[2], CompilerConfig(Language::RISC)};
        }
        if (!CheckOption(argv[3], std::regex("^(C|RISC-V)$"))) {
            throw CliParserException(
                "Invalid target language: expected 'C' or 'RISC-V as the third argument'");
        }
        if (argv[3] == std::string("C")) {
            return {argv[1], argv[2], CompilerConfig(Language::C)};
        }
        return {argv[1], argv[2], CompilerConfig(Language::RISC)};
    };

private:
    bool CheckOption(std::string option, std::regex validator) {
        return std::regex_match(option, validator);
    }
};
}  // namespace cliparser
