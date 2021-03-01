//
// Created by Ahmad Beirkdar on 2021-02-22.
//

#include "lexer.h"

[[nodiscard]]
auto Lexer::get_token() -> std::unique_ptr<token> {
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
        return std::make_unique<token>(Kind::Identifier,std::make_any<std::string>(identifier),location.first,location.second);
    }

    // Get number
    if(isdigit(last_char)){
        value = "";
        while(isdigit(last_char) || last_char == '.'){
            value += last_char;
            this->get_char();
        }
        return (value.find('.') == std::string::npos) ?
                    std::make_unique<token>(Kind::I32,std::make_any<int32_t>(std::stoi(value)),location.first,location.second) :
                    std::make_unique<token>(Kind::F32,std::make_any<double>(std::stod(value)),location.first,location.second);
    }

    if(last_char == '"'){
        this->get_char();
        value = "";
        while(isalnum(last_char)){
            value += last_char;
            this->get_char();
        }
        return std::make_unique<token>(Kind::Str,std::make_any<std::string>(value),location.first,location.second);
    }

    if(last_char == ':'){
        this->get_char();
        if(last_char == '=')
            return std::make_unique<token>(Kind::Assignment,location.first,location.second);

        value = "";
        while(isspace(last_char))
            this->get_char();

        while(isalnum(last_char)){
            value += last_char;
            this->get_char();
        }

        // TODO: Get type name

    }

    // Ignore Comment
    if(last_char == '#'){
        while(last_char != EOF && last_char != '\n')
            this->get_char();
        return this->get_token();
    }

    return std::make_unique<token>(Kind::Nil,location.first,location.second);

}

auto Lexer::get_char() -> void {
    if(last_char == '\n'){
        location.first++;
        location.second = 1;
    }
    else
        location.second++;
    last_char = in->get();
}
