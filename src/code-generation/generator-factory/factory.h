#ifndef GENERATOR_FACTORY_H
#define GENERATOR_FACTORY_H

#include "../generators/c-codegenerator/Ccodegenerator.h"
#include "../generators/codegenerator.h"
#include "../generators/risc-codegenerator/risccodegenerator.h"

namespace compiler::codegenerator {
std::unique_ptr<ICodeGenerator> CreateGenerator(configs::Language language,
                                                configs::FormattingConfig& formatting_config) {
    switch (language) {
        case configs::Language::C:
            return std::make_unique<CodeGenerator<configs::Language::C>>(formatting_config);
            break;
        case configs::Language::RISC:
            return std::make_unique<CodeGenerator<configs::Language::RISC>>(formatting_config);
            break;
        default:
            break;
    }
    throw std::runtime_error("Unknown language");
}
}  // namespace compiler::codegenerator
#endif