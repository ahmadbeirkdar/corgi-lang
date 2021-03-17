//
// Created by Ahmad Beirkdar on 2021-02-25.
//

#ifndef CORGI_LANG_PARSER_H
#define CORGI_LANG_PARSER_H
#include "lexer.h"
#include "AST.h"
#include <iostream>

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


};


#endif //CORGI_LANG_PARSER_H
