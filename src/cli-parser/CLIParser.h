#include <iostream>
#include <regex>
#include <unordered_map>

#include "../configs/configs.h"
namespace cliparser {
using namespace compiler::configs;
class CLIParser {
public:
    explicit CLIParser() {}

    std::tuple<std::string, std::string, CompilerConfig> Parse(char** argv, int argc) {
        // do not count ./main
        if (argc - 1 > 3) {
            throw std::runtime_error("Too many arguments provided");
        }
        if (argc - 1 < 2) {
            throw std::runtime_error("Too few arguments provided");
        }
        if (!CheckOption(argv[1], std::regex("^.*\\.mlang$"))) {
            throw std::runtime_error("Wrong input file");
        }
        if (!CheckOption(argv[2], std::regex("^.*\\.(c|s|txt)$"))) {
            throw std::runtime_error("Wrong output file");
        }
        if (argc - 1 != 3) {
            return {argv[1], argv[2], CompilerConfig(Language::RISC)};
        }
        if (!CheckOption(argv[3], std::regex("^(C|RISC-V)$"))) {
            throw std::runtime_error("Expected C|RISC-V as third argument");
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
