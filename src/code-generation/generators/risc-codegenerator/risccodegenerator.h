#ifndef RISC_CODEGENERATOR
#define RISC_CODEGENERATOR

#include "../../../exceptions/exceptions.h"
#include "../codegenerator.h"

namespace compiler::codegenerator {

using namespace exceptions;

template <>
class CodeGenerator<configs::Language::RISC> : public ICodeGenerator {
public:
    explicit CodeGenerator(configs::FormattingConfig const& formatting_config)
        : formatting_config_(formatting_config), if_counter_(0), while_counter_(0) {}
    void Visit(NumberExpression const* node) override {
        code_ += formatting_config_.GetIndent() + "li ";
        result_register_ = allocator_.Allocate().value();
        code_ += result_register_ + ", " + std::to_string(node->GetValue()) + "\n";
    };

    void Visit(VariableExpression const* node) override {
        if (table_.CheckSymbol(node->GetName())) {
            code_ += formatting_config_.GetIndent() + "lw ";
            result_register_ = allocator_.Allocate().value();
            code_ += result_register_ + ", " + table_.GetOffset(node->GetName()) + "\n";
        } else {
            throw CompilerException("Code generation error: variable '" + node->GetName() +
                                    "' is not declared");
        }
    }

    void Visit(BinaryExpression const* node) override {
        node->GetLeftExpression()->Accept(this);
        std::string left_register = result_register_;
        std::string spill_reg = table_.Spill();
        code_ += formatting_config_.GetIndent() + "sw " + left_register + ", " + spill_reg + "\n";
        allocator_.Free(left_register);
        node->GetRightExpression()->Accept(this);
        std::string right_register = result_register_;
        switch (node->GetOP().type_) {
            case TokenType::PLUS:
                left_register = allocator_.Allocate().value();
                code_ += formatting_config_.GetIndent() + "lw " + left_register + ", " + spill_reg +
                         "\n";
                code_ += formatting_config_.GetIndent() + "add " + left_register + ", " +
                         left_register + ", " + right_register + "\n";
                break;
            case TokenType::MINUS:
                left_register = allocator_.Allocate().value();
                code_ += formatting_config_.GetIndent() + "lw " + left_register + ", " + spill_reg +
                         "\n";
                code_ += formatting_config_.GetIndent() + "sub " + left_register + ", " +
                         left_register + ", " + right_register + "\n";
                break;
            case TokenType::MULTIPLY:
                left_register = allocator_.Allocate().value();
                code_ += formatting_config_.GetIndent() + "lw " + left_register + ", " + spill_reg +
                         "\n";
                code_ += formatting_config_.GetIndent() + "mul " + left_register + ", " +
                         left_register + ", " + right_register + "\n";
                break;
            case TokenType::DIVIDE:
                left_register = allocator_.Allocate().value();
                code_ += formatting_config_.GetIndent() + "lw " + left_register + ", " + spill_reg +
                         "\n";
                code_ += formatting_config_.GetIndent() + "div " + left_register + ", " +
                         left_register + ", " + right_register + "\n";
                break;
            case TokenType::LESS:
                left_register = allocator_.Allocate().value();
                code_ += formatting_config_.GetIndent() + "lw " + left_register + ", " + spill_reg +
                         "\n";
                code_ += formatting_config_.GetIndent() + "slt " + left_register + ", " +
                         left_register + ", " + right_register + "\n";
                break;
            case TokenType::MORE:
                left_register = allocator_.Allocate().value();
                code_ += formatting_config_.GetIndent() + "lw " + left_register + ", " + spill_reg +
                         "\n";
                code_ += formatting_config_.GetIndent() + "slt " + left_register + ", " +
                         right_register + ", " + left_register + "\n";
                break;
            default:
                break;
        }
        allocator_.Free(right_register);
        result_register_ = left_register;
    }

    void Visit(UnaryExpression const* node) override {
        node->GetExpression()->Accept(this);
        if (node->IsNegative()) {
            code_ += formatting_config_.GetIndent() + "neg " + result_register_ + ", " +
                     result_register_ + "\n";
        }
    }

    void Visit(AssignmentStatement const* node) override {
        node->GetExpression()->Accept(this);
        table_.ResetSpill();
        table_.AddSymbol(node->GetName());
        code_ += formatting_config_.GetIndent() + "sw " + result_register_ + ", " +
                 table_.GetOffset(node->GetName()) + "\n";
        allocator_.Reset();
    }

    void Visit(IfStatement const* node) override {
        if_counter_++;
        std::string if_mark = std::to_string(if_counter_);
        node->GetCondition()->Accept(this);
        code_ += formatting_config_.GetIndent() + "beqz " + result_register_ + ", " + "skip_if" +
                 if_mark + "\n";
        allocator_.Free(result_register_);
        SymbolTable temp = table_;
        for (auto const& body_statement : node->GetBody()) {
            body_statement->Accept(this);
        }
        table_ = temp;
        code_ += "skip_if" + if_mark + ":\n";
    }

    void Visit(WhileStatement const* node) override {
        while_counter_++;
        std::string while_mark = std::to_string(while_counter_);
        code_ += "while_start" + while_mark + ":\n";
        node->GetCondition()->Accept(this);
        code_ += formatting_config_.GetIndent() + "beqz " + result_register_ + ", while_end" +
                 while_mark + "\n";
        allocator_.Free(result_register_);
        SymbolTable temp = table_;
        for (auto const& body_statement : node->GetBody()) {
            body_statement->Accept(this);
        }
        table_ = temp;
        code_ += formatting_config_.GetIndent() + "j while_start" + while_mark + "\n";
        code_ += "while_end" + while_mark + ":\n";
    }

    std::string Generate(std::vector<std::unique_ptr<ASTNode>> const& ast) override {
        code_ = ".text\n.global _start\n_start:\n";
        formatting_config_.AdvanceIndent();
        for (auto const& node : ast) {
            node->Accept(this);
        }
        code_ += formatting_config_.GetIndent() + "li a7, 93\necall\n";
        return code_;
    }

private:
    std::string code_;
    std::string result_register_;
    SymbolTable table_;
    RegisterAllocator allocator_;
    configs::FormattingConfig formatting_config_;
    int if_counter_;
    int while_counter_;
};
}  // namespace compiler::codegenerator
#endif