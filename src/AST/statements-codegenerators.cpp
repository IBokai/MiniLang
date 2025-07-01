#include "statements.h"

static int if_counter = 0;
static int while_counter = 0;

std::string AssignmentStatement::GetC(SymbolTable& table, FormattingConfig& config) {
    if (!table.CheckSymbol(name_)) {
        std::string result = config.GetIndent() + "int " + name_ + " = ";
        result += expression_->GetC(table, config);
        result += ";";
        table.AddSymbol(name_);
        return result;
    } else {
        std::string result = config.GetIndent() + name_ + " = ";
        result += expression_->GetC(table, config);
        result += ";";
        return result;
    }
}

RiscCodegenOutput AssignmentStatement::GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                                               FormattingConfig& formatting_config) {
    std::string code = "";
    table.AddSymbol(name_);
    RiscCodegenOutput expression_codegen =
        expression_->GetRisc(table, allocator, formatting_config);
    code += expression_codegen.code;

    code += formatting_config.GetIndent() + "sw " + expression_codegen.reg.value() + " " +
            table.GetOffset(name_) + "\n";
    allocator.Reset();
    table.ResetSpill();
    return {code, std::nullopt};
}

std::string IfStatement::GetC(SymbolTable& table, FormattingConfig& config) {
    std::string code = config.GetIndent() + "if (" + condition_->GetC(table, config) + ") {\n";
    config.AdvanceIndent();
    SymbolTable local_table = table;
    for (auto const& body_statement : body_) {
        code += body_statement->GetC(local_table, config) + "\n";
    }
    config.DecreaseIndent();
    code += config.GetIndent() + "}";
    return code;
}

RiscCodegenOutput IfStatement::GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                                       FormattingConfig& formatting_config) {
    if_counter++;
    std::string if_mark = std::to_string(if_counter);
    std::string code = "";
    auto condition_codegen = condition_->GetRisc(table, allocator, formatting_config);
    code += condition_codegen.code;
    std::string reg = condition_codegen.reg.value();
    code += formatting_config.GetIndent() + "beqz " + reg + " " + "skip_if" + if_mark + "\n";
    allocator.Free(reg);
    SymbolTable local_table = table;
    for (auto const& body_statement : body_) {
        code += body_statement->GetRisc(local_table, allocator, formatting_config).code;
    }
    code += "skip_if" + if_mark + ":\n";
    return {code, std::nullopt};
}

std::string WhileStatement::GetC(SymbolTable& table, FormattingConfig& config) {
    std::string code = config.GetIndent() + "while (" + condition_->GetC(table, config) + ") {\n";
    config.AdvanceIndent();
    SymbolTable local_table = table;
    for (auto const& body_statement : body_) {
        code += body_statement->GetC(local_table, config) + "\n";
    }
    config.DecreaseIndent();
    code += config.GetIndent() + "}";
    return code;
}

RiscCodegenOutput WhileStatement::GetRisc(SymbolTable& table, RegisterAllocator& allocator,
                                          FormattingConfig& formatting_config) {
    while_counter++;
    std::string while_mark = std::to_string(while_counter);
    std::string code = "while_start" + while_mark + ":\n";
    auto condition_codegen = condition_->GetRisc(table, allocator, formatting_config);
    code += condition_codegen.code;
    std::string reg = condition_codegen.reg.value();
    code += formatting_config.GetIndent() + "beqz " + reg + " while_end" + while_mark + "\n";
    allocator.Free(reg);
    SymbolTable local_table = table;
    for (auto const& body_statement : body_) {
        code += body_statement->GetRisc(local_table, allocator, formatting_config).code;
    }
    code += formatting_config.GetIndent() + "j while_start" + while_mark + "\n";
    code += "while_end" + while_mark + ":\n";
    return {code, std::nullopt};
}