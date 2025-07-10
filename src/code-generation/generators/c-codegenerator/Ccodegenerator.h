#ifndef C_CODEGENERATOR
#define C_CODEGENERATOR

#include "../../../exceptions/exceptions.h"
#include "../codegenerator.h"

namespace compiler::codegenerator {

using namespace exceptions;

template <>
class CodeGenerator<configs::Language::C> : public ICodeGenerator {
public:
    explicit CodeGenerator(configs::FormattingConfig& formatting_config)
        : formatting_config_(formatting_config) {}

    void Visit(NumberExpression const* node) override { code_ += std::to_string(node->GetValue()); }

    void Visit(VariableExpression const* node) override {
        if (table_.CheckSymbol(node->GetName())) {
            code_ += node->GetName();
        } else {
            throw CompilerException("Code generation error: variable '" + node->GetName() +
                                    "' is not declared");
        }
    }

    void Visit(BinaryExpression const* node) override {
        code_ += "(";
        node->GetLeftExpression()->Accept(this);
        code_ += " " + node->GetOP().text_ + " ";
        node->GetRightExpression()->Accept(this);
        code_ += ")";
    }

    void Visit(UnaryExpression const* node) override {
        if (node->IsNegative()) {
            code_ += "-";
        }
        node->GetExpression()->Accept(this);
    }

    void Visit(AssignmentStatement const* node) override {
        if (!table_.CheckSymbol(node->GetName())) {
            code_ += formatting_config_.GetIndent() + "int " + node->GetName() + " = ";
            node->GetExpression()->Accept(this);
            code_ += ";\n";
            table_.AddSymbol(node->GetName());
        } else {
            code_ += formatting_config_.GetIndent() + node->GetName() + " = ";
            node->GetExpression()->Accept(this);
            code_ += ";\n";
        }
    }

    void Visit(IfStatement const* node) override {
        code_ += formatting_config_.GetIndent() + "if (";
        node->GetCondition()->Accept(this);
        code_ += ") {\n";
        formatting_config_.AdvanceIndent();
        // creating temporary table, now table_ is local for if-statement body
        SymbolTable temp = table_;
        for (auto const& body_statement : node->GetBody()) {
            body_statement->Accept(this);
        }
        // return table_ to temporary table
        table_ = temp;
        formatting_config_.DecreaseIndent();
        code_ += formatting_config_.GetIndent() + "}\n";
    }

    void Visit(WhileStatement const* node) override {
        code_ += formatting_config_.GetIndent() + "while (";
        node->GetCondition()->Accept(this);
        code_ += ") {\n";
        formatting_config_.AdvanceIndent();
        // creating temporary table, now table_ is local for while-statement body
        SymbolTable temp = table_;
        for (auto const& body_statement : node->GetBody()) {
            body_statement->Accept(this);
        }
        // return table_ to temporary table
        table_ = temp;
        formatting_config_.DecreaseIndent();
        code_ += formatting_config_.GetIndent() + "}\n";
    }

    std::string Generate(std::vector<std::unique_ptr<ASTNode>> const& ast) override {
        code_ = "int main() {\n";
        formatting_config_.AdvanceIndent();
        for (auto const& node : ast) {
            node->Accept(this);
        }
        code_ += formatting_config_.GetIndent() + "return 0;\n}\n";
        return code_;
    }

private:
    std::string code_;
    SymbolTable table_;
    configs::FormattingConfig formatting_config_;
};
}  // namespace compiler::codegenerator
#endif