#pragma once
#include <string>
#include <unordered_set>

class SymbolTable {
public:
    SymbolTable() : table_({}) {}

    void AddSymbol(std::string symbol) { table_.insert(symbol); }

    bool CheckSymbol(std::string const& symbol) {
        if (table_.count(symbol)) {
            return true;
        }
        return false;
    }

private:
    std::unordered_set<std::string> table_;
};