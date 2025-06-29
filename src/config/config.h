#pragma once
#include <string>

enum class Language { C, RISC };

class CompilerConfig {
public:
    explicit CompilerConfig(Language language = Language::RISC, size_t indent_size = 0)
        : language_(language), indent_size_(indent_size) {}

    std::string GetIndent() const { return std::string(indent_size_, ' '); }
    void AdvanceIndent(size_t step = 4) { indent_size_ += step; }
    void DecreaseIndent(size_t step = 4) { indent_size_ -= step; }

    Language GetLanguage() const { return language_; }

private:
    Language language_;
    size_t indent_size_;
};