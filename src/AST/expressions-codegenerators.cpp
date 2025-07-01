#include "expressions.h"

std::string NumberExpression::GetC([[maybe_unused]] SymbolTable& table,
                                   [[maybe_unused]] FormattingConfig& config) {
    return std::to_string(value_);
}

RiscCodegenOutput NumberExpression::GetRisc([[maybe_unused]] SymbolTable& table,
                                            RegisterAllocator& allocator) {
    std::string code = "li ";
    std::string reg = allocator.Allocate().value();
    code += reg + " " + std::to_string(value_) + "\n";
    return {code, reg};
}

std::string VariableExpression::GetC(SymbolTable& table,
                                     [[maybe_unused]] FormattingConfig& config) {
    if (table.CheckSymbol(name_)) {
        return name_;
    }
    throw std::runtime_error(
        "Error while compiling variable expression, no variable with such name declared");
}

RiscCodegenOutput VariableExpression::GetRisc(SymbolTable& table, RegisterAllocator& allocator) {
    if (table.CheckSymbol(name_)) {
        std::string code = "lw ";
        std::string reg = allocator.Allocate().value();
        code += reg + " " + table.GetOffset(name_) + "\n";
        return {code, reg};
    }
    throw std::runtime_error(
        "Error while compiling variable expression, no variable with such name declared");
}

std::string BinaryExpression::GetC(SymbolTable& table, FormattingConfig& config) {
    return "(" + left_->GetC(table, config) + " " + op_.text_ + " " + right_->GetC(table, config) +
           ")";
}

RiscCodegenOutput BinaryExpression::GetRisc(SymbolTable& table, RegisterAllocator& allocator) {
    std::string code = "";
    auto left_expreesion_codegen = left_->GetRisc(table, allocator);
    code += left_expreesion_codegen.code;
    std::string left_reg = left_expreesion_codegen.reg.value();
    std::string spill_reg = table.Spill();
    code += "sw " + left_reg + " " + spill_reg + "\n";
    allocator.Free(left_reg);
    auto right_expreesion_codegen = right_->GetRisc(table, allocator);
    code += right_expreesion_codegen.code;
    std::string right_reg = right_expreesion_codegen.reg.value();
    switch (op_.type_) {
        case TokenType::PLUS:
            left_reg = allocator.Allocate().value();
            code += "lw " + left_reg + " " + spill_reg + "\n";
            code += "add " + left_reg + " " + left_reg + " " + right_reg + "\n";
            break;
        case TokenType::MINUS:
            left_reg = allocator.Allocate().value();
            code += "lw " + left_reg + " " + spill_reg + "\n";
            code += "sub " + left_reg + " " + left_reg + " " + right_reg + "\n";
            break;
        case TokenType::MULTIPLY:
            left_reg = allocator.Allocate().value();
            code += "lw " + left_reg + " " + spill_reg + "\n";
            code += "mul " + left_reg + " " + left_reg + " " + right_reg + "\n";
            break;
        case TokenType::DIVIDE:
            left_reg = allocator.Allocate().value();
            code += "lw " + left_reg + " " + spill_reg + "\n";
            code += "div " + left_reg + " " + left_reg + " " + right_reg + "\n";
            break;
        case TokenType::LESS:
            left_reg = allocator.Allocate().value();
            code += code += "lw " + left_reg + " " + spill_reg + "\n";
            code += "slt " + left_reg + " " + left_reg + " " + right_reg + "\n";
            break;
        case TokenType::MORE:
            left_reg = allocator.Allocate().value();
            code += code += "lw " + left_reg + " " + spill_reg + "\n";
            code += "slt " + left_reg + " " + right_reg + " " + left_reg + "\n";
            break;
        default:
            break;
    }
    allocator.Free(right_reg);
    return {code, left_reg};
}

std::string UnaryExpression::GetC(SymbolTable& table, FormattingConfig& config) {
    if (negative_) {
        return "-" + expression_->GetC(table, config);
    }
    return expression_->GetC(table, config);
}

RiscCodegenOutput UnaryExpression::GetRisc(SymbolTable& table, RegisterAllocator& allocator) {
    std::string code = "";
    auto expression_codegen = expression_->GetRisc(table, allocator);
    code = expression_codegen.code;
    code += "neg " + expression_codegen.reg.value() + " " + expression_codegen.reg.value() + "\n";
    return {code, expression_codegen.reg.value()};
}