#ifndef CONFIGS_H
#define CONFIGS_H

#include <string>

namespace compiler::configs {
enum class Language { C, RISC };

class CompilerConfig {
public:
    explicit CompilerConfig(Language language = Language::RISC) : language_(language) {}

    Language GetLanguage() const { return language_; }

private:
    Language language_;
};

class FormattingConfig {
public:
    explicit FormattingConfig(size_t indent_size = 0) : indent_size_(indent_size) {}

    std::string GetIndent() const { return std::string(indent_size_, ' '); }
    void AdvanceIndent(size_t step = 4) { indent_size_ += step; }
    void DecreaseIndent(size_t step = 4) { indent_size_ -= step; }

private:
    size_t indent_size_;
};
}  // namespace compiler::configs
#endif