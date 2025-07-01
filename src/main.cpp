#include <fstream>
#include <iostream>
#include <string>

#include "code-generation/codegenerator.h"
#include "compiler/compiler.h"
#include "configs/configs.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "util/processinput.h"

int main(int argc, char* argv[]) {
    std::string const input = ProcessInput(argv, argc);
    CompilerConfig config(Language::RISC);
    Compiler compiler = Compiler(config);
    compiler.Compile(input, "../temporary-output/output.txt");
    return 0;
}