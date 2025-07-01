#include <fstream>
#include <iostream>
#include <string>

#include "code-generation/codegenerator.h"
#include "compiler/compiler.h"
#include "configs/configs.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "util/processinput.h"
#include "cli-parser/CLIParser.h"

int main(int argc, char* argv[]) {
    CLIParser cli_parser = CLIParser();
    auto [input, output, config] = cli_parser.Parse(argv, argc);
    Compiler compiler = Compiler(config);
    compiler.Compile(input, output);
    return 0;
}