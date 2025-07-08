#include <iostream>
#include <string>

#include "cli-parser/CLIParser.h"
#include "compiler/compiler.h"
#include "configs/configs.h"

int main(int argc, char* argv[]) {
    cliparser::CLIParser cli_parser = cliparser::CLIParser();
    try {
        auto [input, output, config] = cli_parser.Parse(argv, argc);
        try {
            compiler::Compiler compiler = compiler::Compiler(config);
            compiler.Compile(input, output);
        } catch (const std::exception& e) {
            std::cerr << "Compilation error: " << e.what() << '\n';
        }

    } catch (const std::exception& e) {
        std::cerr << "Command line arguments error: " << e.what() << '\n';
    }

    return 0;
}