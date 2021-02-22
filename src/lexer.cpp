//
// Created by Ahmad Beirkdar on 2021-02-22.
//

#include "lexer.h"

[[nodiscard]]
auto lexer::get_token() -> Kind {
    while(isspace(last_char))
        this->get_char();

    // Check EOF
    if(last_char == EOF)
        return Kind::EndOfFile;

    // Get identifier
    if(isalpha(last_char)){
        identifier = last_char;

        this->get_char();
        while(isalnum(last_char)){
            identifier += last_char;
            this->get_char();
        }

        if(identifier == "def")
            return Kind::Def;
        return Kind::Identifier;
    }

    // Get number
    if(isdigit(last_char)){
        while(isdigit(last_char) || last_char == '.'){
            value += last_char;
            this->get_char();
        }
        return (value.find('.') == std::string::npos) ? Kind::I32 : Kind::F32;
    }

    if(last_char == '"'){
        this->get_char();
        while(isalnum(last_char)){
            value += last_char;
            this->get_char();
        }
        return Kind::Str;
    }

    // Ignore Comment
    if(last_char == '#'){
        while(last_char != EOF && last_char != '\n')
            this->get_char();
        return this->get_token();
    }

    return Kind::Nil;

}

auto lexer::get_char() -> void {
    if(last_char == '\n'){
        location.first++;
        location.second = 1;
    }
    else
        location.second++;
    last_char = in->get();
}
