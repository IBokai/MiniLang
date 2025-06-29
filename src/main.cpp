#include <fstream>
#include <iostream>
#include <string>

#include "code-generation/codegenerator.h"
#include "compiler/compiler.h"
#include "config/config.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "util/processinput.h"

int main(int argc, char* argv[]) {
    std::string const input = ProcessInput(argv, argc);
    CompilerConfig config(Language::C);
    Compiler compiler = Compiler(config);
    std::ofstream output("../temporary-output/output.c");
    output.clear();
    std::string code = compiler.Compile(input);
    output << code;
    return 0;
}