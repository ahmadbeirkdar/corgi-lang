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

auto parser::ParseExpr() -> std::unique_ptr<ExprAST> {
    return std::unique_ptr<ExprAST>();
}

auto parser::ParseI8Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<i8ExprAST>(curr_token->get_value<int8_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseI16Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<i16ExprAST>(curr_token->get_value<int16_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseI32Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<i32ExprAST>(curr_token->get_value<int32_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseI64Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<i64ExprAST>(curr_token->get_value<int64_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseU8Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<u8ExprAST>(curr_token->get_value<u_int8_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseU16Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<u16ExprAST>(curr_token->get_value<u_int16_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseU32Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<u32ExprAST>(curr_token->get_value<u_int32_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseU64Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<u64ExprAST>(curr_token->get_value<u_int64_t>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseF32Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<f32ExprAST>(curr_token->get_value<double>());
    this->getNextToken();
    return std::move(res);
}

auto parser::ParseParenExpr() -> std::unique_ptr<ExprAST> {
    this->getNextToken();
    auto res = this->ParseExpr();

    if(!res)
        return nullptr;

    if(this->curr_token->get_value<char>() != ')')
        return LogError("Missing ')'");

    this->ParseExpr();
    return res;
}

auto parser::ParseIdentifierExpr() -> std::unique_ptr<ExprAST> {
    auto name = this->curr_token->get_value<std::string>();

    this->getNextToken();

    if(this->curr_token->get_value<char>() != '(')
        return std::make_unique<VariableExprAST>(name);

    // Otherwise if here, its a function call
    this->getNextToken();
    std::vector<std::unique_ptr<ExprAST>> fun_args;
    if(this->curr_token->get_value<char>() != ')'){
        while (1) {
            auto arg = ParseExpr();
            if (arg)
                fun_args.push_back(std::move(arg));
            else
                return nullptr;
            if (this->curr_token->get_value<char>() != ')')
                break;
            if(this->curr_token->get_value<char>() != ',')
                return LogError("Missing ',' or ')' in the arguments of function: " + name);
            this->getNextToken();
        }

    }
    this->getNextToken();
    return std::make_unique<FunctionCallExprAST>(name,fun_args);
}
