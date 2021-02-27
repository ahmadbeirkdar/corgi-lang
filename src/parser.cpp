//
// Created by Ahmad Beirkdar on 2021-02-25.
//

#include "parser.h"

auto parser::getNextToken() -> std::unique_ptr<token>& {
    this->curr_token = this->lexer.get_token();
    return this->curr_token;
}

auto parser::LogError(const std::string_view& str) -> std::unique_ptr<ExprAST> {
    std::cerr << "LogError: " << str << "\n";
    return nullptr;
}

auto parser::LogErrorPrototype(const std::string_view &str) -> std::unique_ptr<FunctionPrototypeExprAST> {
    LogError(str);
    return nullptr;
}

auto parser::ParseI32Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<i32ExprAST>(curr_token->get_value<int32_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseF32Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<f32ExprAST>(curr_token->get_value<double>());
    this->getNextToken();
    return std::move(res);
}
