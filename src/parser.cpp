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
