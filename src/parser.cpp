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
    auto res = std::make_unique<f32ExprAST>(curr_token->get_value<float>());
    this->getNextToken();
    return std::move(res);
}
auto parser::ParseF64Expr() -> std::unique_ptr<ExprAST> {
    auto res = std::make_unique<f64ExprAST>(curr_token->get_value<double>());
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
    this->getNextToken(); // Take (
    std::vector<std::unique_ptr<ExprAST>> fun_args;
    if(this->curr_token->get_value<char>() != ')'){
        while (true) {
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
    return std::make_unique<FunctionCallExprAST>(name,std::move(fun_args));
}

auto parser::ParsePrimary() -> std::unique_ptr<ExprAST> {
    switch (this->curr_token->get_kind()) {
        case Kind::I8:
            return this->ParseI8Expr();
        case Kind::I16:
            return this->ParseI16Expr();
        case Kind::I32:
            return this->ParseI32Expr();
        case Kind::I64:
            return this->ParseI64Expr();
        case Kind::U8:
            return this->ParseU8Expr();
        case Kind::U16:
            return this->ParseU16Expr();
        case Kind::U32:
            return this->ParseU32Expr();
        case Kind::U64:
            return this->ParseU64Expr();
        case Kind::F32:
            return this->ParseF32Expr();
        case Kind::F64:
            return this->ParseF64Expr();
        case Kind::Identifier:
            return this->ParseIdentifierExpr();
        default:
            if(this->curr_token->get_value<char>() == '(')
                return this->ParseParenExpr();
            return this->LogError("Error: Unknown token.");
    }
}

auto parser::getTokenPrecedence() -> int32_t {
    auto curr = this->curr_token->get_value<char>();
    if(!isascii(curr))
        return -1; // Not ascii, thus bad

    if(parser::BinaryPrecedence.count(curr))
        return parser::BinaryPrecedence.at(curr);
    return -1; // Not found in map, thus bad
}

auto parser::ParseBinaryOpRHS(int32_t exprPre, std::unique_ptr<ExprAST> LHS) -> std::unique_ptr<ExprAST> {
    while(true){
        auto tokenPre = this->getTokenPrecedence();

        // Binary operation(s) done.
        if(tokenPre < exprPre)
            return LHS;

        // Otherwise not done yet...
        char operation = this->curr_token->get_value<char>();
        this->getNextToken(); // Take the operation, move to next

        auto RHS = this->ParsePrimary(); // Parse primary for RHS
        // If parsing was invalid
        if(!RHS)
            return nullptr;

        auto nextPre = this->getTokenPrecedence();
        if(tokenPre < nextPre){
            RHS = ParseBinaryOpRHS(tokenPre+1,std::move(RHS));
            if(!RHS)
                return nullptr;
        }
        LHS = std::make_unique<BinaryExprAST>(operation,std::move(LHS),std::move(RHS));
    }
}

