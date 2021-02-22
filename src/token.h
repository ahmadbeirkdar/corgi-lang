//
// Created by Ahmad Beirkdar on 2021-02-22.
//

#ifndef CORGI_LANG_TOKEN_H
#define CORGI_LANG_TOKEN_H
#include <any>

enum Kind{
    EndOfFile,Def,Extern,Identifier,Nil
    Str,Bool,Char,Array,
    U8,U16,U32,U64,
    I8,I16,I32,I64,
    F32,F64,
};

template<typename T = void*>
class token {
public:

    token()=default;
    token(Kind kind, T value, uint32_t line = 0, uint32_t column = 0)
        : kind(kind), value(std::make_any<T>(value)), location(line,column) {}

    auto get_value()  -> T          {return value.has_value() ? std::any_cast<T>(value) : std::any();}
    auto get_kind()   -> Kind       {return kind;}
    auto get_line()   -> uint32_t   {return location.first;}
    auto get_column() -> uint32_t   {return location.second;}

private:
    std::any value{};
    std::pair<uint32_t,uint32_t> location{0,0}; // <line,column>
    Kind kind{EndOfFile};
};


#endif //CORGI_LANG_TOKEN_H
