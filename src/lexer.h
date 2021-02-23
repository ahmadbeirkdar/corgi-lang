//
// Created by Ahmad Beirkdar on 2021-02-22.
//

#ifndef CORGI_LANG_LEXER_H
#define CORGI_LANG_LEXER_H
#include <istream>
#include "token.h"

class lexer {
public:
    lexer()=delete;
    lexer(std::istream *in)
        : in(in) {get_token();};

    std::pair<uint32_t,uint32_t> location;
    Kind kind;
    char last_char = ' ';

private:
    auto get_token() -> std::unique_ptr<token>;
    auto get_char()  -> void;
    std::istream *in;
    std::string identifier;
    std::string value;



};


#endif //CORGI_LANG_LEXER_H
