//
// Created by Ahmad Beirkdar on 2021-02-25.
//

#ifndef CORGI_LANG_PARSER_H
#define CORGI_LANG_PARSER_H
#include "lexer.h"
#include "AST.h"
#include <iostream>
#include <unordered_map>

class parser {
public:
    parser();

private:
    Lexer lexer;
    std::unique_ptr<token> curr_token;

           auto getNextToken()                                      -> std::unique_ptr<token>&;
    static auto LogError(const std::string_view& str)               -> std::unique_ptr<ExprAST>;
    static auto LogErrorPrototype(const std::string_view& str)      -> std::unique_ptr<FunctionPrototypeExprAST>;

    auto ParseExpr()             -> std::unique_ptr<ExprAST>;
    auto ParseI8Expr()           -> std::unique_ptr<ExprAST>;
    auto ParseI16Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseI32Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseI64Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseU8Expr()           -> std::unique_ptr<ExprAST>;
    auto ParseU16Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseU32Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseU64Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseF32Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseF64Expr()          -> std::unique_ptr<ExprAST>;
    auto ParseParenExpr()        -> std::unique_ptr<ExprAST>;
    auto ParseIdentifierExpr()   -> std::unique_ptr<ExprAST>;
    auto ParsePrimary()          -> std::unique_ptr<ExprAST>;
    auto ParseBinaryOpRHS(
            int32_t exprPre, std::unique_ptr<ExprAST> LHS
            )                    -> std::unique_ptr<ExprAST>;
    auto ParsePrototype()        -> std::unique_ptr<FunctionPrototypeExprAST>;
    auto ParseExtern()           -> std::unique_ptr<FunctionPrototypeExprAST>;
    auto ParseDefinition()       -> std::unique_ptr<FunctionAST>;
    auto ParseTopLevelExpr()     -> std::unique_ptr<FunctionAST>;

    // Binary Operation Precedence
    const inline static std::unordered_map<char,int32_t> BinaryPrecedence = {
            {'<', 10},
            {'+', 20},
            {'-', 30},
            {'*', 40},
            {'/', 50}
    };

    auto getTokenPrecedence()   -> int32_t;


};


#endif //CORGI_LANG_PARSER_H
