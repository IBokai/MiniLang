#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace compiler::exceptions {
class CompilerException : public std::runtime_error {
public:
    explicit CompilerException(std::string const& msg) : std::runtime_error(msg) {}
};

class CliParserException : public std::runtime_error {
public:
    explicit CliParserException(std::string const& msg) : std::runtime_error(msg) {}
};
}  // namespace compiler::exceptions
#endif
