#ifndef PROCESSINPUT_H
#define PROCESSINPUT_H

#include <stdexcept>
#include <string>

inline std::string processinput(char const* argv[], int argc) {
    if (argc < 2) {
        throw std::runtime_error("No file provided");
    }
    if (argc > 2) {
        throw std::runtime_error(
            "Multiple command line arguments provided. This compiler does not support any "
            "flags");
    }
    std::string result = argv[1];
    return result;
}
#endif