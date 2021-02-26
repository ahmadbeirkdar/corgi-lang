//
// Created by Ahmad Beirkdar on 2021-02-25.
//

#ifndef CORGI_LANG_AST_H
#define CORGI_LANG_AST_H
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>
#include <string>


class ExprAST{
public:
    virtual ~ExprAST() = default;
};

class VariableExprAST: ExprAST{
public:
    explicit VariableExprAST(std::string name) : name(std::move(name)) {};
private:
    std::string name;
};

class i32ExprAST: ExprAST{
public:
    explicit i32ExprAST(int32_t value) : value(value) {};
private:
    int32_t value;
};

class f32ExprAST: ExprAST{
public:
    explicit f32ExprAST(float value) : value(value) {};
private:
    float value;
};

class BinaryExprAST: ExprAST{
public:
    BinaryExprAST(char operation,std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
        : operation(operation), LHS(std::move(LHS)), RHS(std::move(RHS))  {};
private:
    std::unique_ptr<ExprAST> RHS, LHS;
    char operation;
};

class FunctionCallExprAST : public ExprAST {
public:
    FunctionCallExprAST(std::string callee, std::vector<std::unique_ptr<ExprAST>> args)
            : callee(std::move(callee)), args(std::move(args)) {}
private:
    std::string callee;
    std::vector<std::unique_ptr<ExprAST>> args;
};

class FunctionPrototypeExprAST : public ExprAST {
public:
    FunctionPrototypeExprAST(std::string name, std::vector<std::string> args)
            : name(std::move(name)), args(std::move(args)) {}
private:
    std::string name;
    std::vector<std::string> args;
};

class FunctionAST : public ExprAST {
public:
    FunctionAST(std::unique_ptr<FunctionPrototypeExprAST> prototype, std::unique_ptr<ExprAST> body)
            : prototype(std::move(prototype)), body(std::move(body)) {}
private:
    std::unique_ptr<FunctionPrototypeExprAST> prototype;
    std::unique_ptr<ExprAST> body;
};

#endif //CORGI_LANG_AST_H
