//
// Created by Ahmad Beirkdar on 2021-02-22.
//

#ifndef CORGI_LANG_Lexer_H
#define CORGI_LANG_Lexer_H
#include <istream>
#include <memory>
#include "token.h"

class Lexer {
public:
    Lexer()=delete;
    explicit Lexer(std::istream *in)
        : in(in) {};

    std::pair<uint32_t,uint32_t> location;
    Kind kind;
    char last_char = ' ';

    [[nodiscard]] auto get_token() -> std::unique_ptr<token>;

private:
    auto get_char()  -> void;
    std::istream *in;
    std::string identifier;
    std::string value;



};


#endif //CORGI_LANG_Lexer_H
