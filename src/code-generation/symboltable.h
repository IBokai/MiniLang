#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stack>
#include <string>
#include <unordered_map>
namespace compiler::codegenerator {
class SymbolTable {
public:
    SymbolTable() : current_offset_(-4), spill_count_(0) {}

    void AddSymbol(std::string const& symbol) {
        if (table_.count(symbol) == 0) {
            table_.try_emplace(symbol, std::to_string(current_offset_) + "(sp)");
            current_offset_ -= 4;
        }
    }

    std::string Spill() {
        std::string stack_reg = std::to_string(current_offset_) + "(sp)";
        spill_count_++;
        current_offset_ -= 4;
        return stack_reg;
    }

    void ResetSpill() {
        current_offset_ += 4 * spill_count_;
        spill_count_ = 0;
    }

    std::string GetOffset(std::string const& symbol) { return table_[symbol]; }

    bool CheckSymbol(std::string const& symbol) { return table_.count(symbol) > 0; }

private:
    std::unordered_map<std::string, std::string> table_;
    int current_offset_;
    int spill_count_;
};
}  // namespace compiler::codegenerator
#endif