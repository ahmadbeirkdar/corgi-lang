//
// Created by Ahmad Beirkdar on 2021-02-22.
//

#include "lexer.h"

[[nodiscard]]
auto lexer::get_token() -> std::unique_ptr<token> {
    while(isspace(last_char))
        this->get_char();

    // Check EOF
    if(last_char == EOF)
        return std::make_unique<token>(Kind::EndOfFile,location.first,location.second);

    // Get identifier
    if(isalpha(last_char)){
        identifier = last_char;

        this->get_char();
        while(isalnum(last_char)){
            identifier += last_char;
            this->get_char();
        }

        if(identifier == "def")
            return std::make_unique<token>(Kind::Def,location.first,location.second);
        return std::make_unique<token>(Kind::Identifier,location.first,location.second);
    }

    // Get number
    if(isdigit(last_char)){
        while(isdigit(last_char) || last_char == '.'){
            value += last_char;
            this->get_char();
        }
        return (value.find('.') == std::string::npos) ? std::make_unique<token>(Kind::I32,location.first,location.second) : std::make_unique<token>(Kind::F32,location.first,location.second);
    }

    if(last_char == '"'){
        this->get_char();
        while(isalnum(last_char)){
            value += last_char;
            this->get_char();
        }
        return std::make_unique<token>(Kind::Str,location.first,location.second);
    }

    // Ignore Comment
    if(last_char == '#'){
        while(last_char != EOF && last_char != '\n')
            this->get_char();
        return this->get_token();
    }

    return std::make_unique<token>(Kind::Nil,location.first,location.second);

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

auto lexer::next_token() -> void {
    this->curr_token = this->get_token();
}
