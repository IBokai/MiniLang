#ifndef REGISTER_ALLOCATOR_H
#define REGISTER_ALLOCATOR_H

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
namespace compiler::codegenerator {
class RegisterAllocator {
public:
    RegisterAllocator() : registers_({"t0", "t1", "t2", "t3", "t4", "t5", "t6"}) {
        used_.resize(registers_.size(), false);
    }

    std::optional<std::string> Allocate() {
        for (size_t i = 0; i < used_.size(); i++) {
            if (!used_[i]) {
                used_[i] = true;
                return registers_[i];
            }
        }
        return std::nullopt;
    }

    void Free(std::string const& reg) {
        for (size_t i = 0; i < registers_.size(); i++) {
            if (registers_[i] == reg) {
                used_[i] = false;
                return;
            }
        }
    }

    void Reset() {
        for (size_t i = 0; i < registers_.size(); i++) {
            used_[i] = false;
        }
    }

private:
    std::vector<std::string> registers_;
    std::vector<bool> used_;
};
}  // namespace compiler::codegenerator
#endif