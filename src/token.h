//
// Created by Ahmad Beirkdar on 2021-02-22.
//

#ifndef CORGI_LANG_TOKEN_H
#define CORGI_LANG_TOKEN_H
#include <any>
#include <typeindex>

enum Kind{
    EndOfFile,Def,Extern,Identifier,Nil,
    Str,Bool,Char,Array,
    U8,U16,U32,U64,
    I8,I16,I32,I64,
    F32,F64,
};


class token {
public:

    token()=delete;

    token(Kind kind, uint32_t line = 0, uint32_t column = 0)
            : kind(kind), location(line,column), type(typeid(nullptr)) {}

    template<typename T>
    token(Kind kind, T value, uint32_t line = 0, uint32_t column = 0)
        : kind(kind), value(std::make_any<T>(value)), type(typeid(T)),location(line,column) {}

    template<typename T>
    [[nodiscard]] auto get_value()  const  -> auto       {return std::any_cast<T>(value);}
    [[nodiscard]] auto get_kind()   const  -> Kind       {return kind;}
    [[nodiscard]] auto get_line()   const  -> uint32_t   {return location.first;}
    [[nodiscard]] auto get_column() const  -> uint32_t   {return location.second;}

    std::type_index type;
private:
    std::any value{};
    std::pair<uint32_t,uint32_t> location{0,0}; // <line,column>
    Kind kind{EndOfFile};
};


#endif //CORGI_LANG_TOKEN_H
