#include <iostream>
#include <fstream>
#include "parser.h"

int main() {
    std::ifstream in("../test.corgi",std::ifstream::in);
    Lexer lexer(&in);
    std::unique_ptr<token> t;
    if(in.is_open())
        while ((t = lexer.get_token())->get_kind() != Kind::EndOfFile){
            switch (t->get_kind()) {
                case Def:
                    std::cout << "Def" << std::endl;
                    break;
                case Extern:
                    std::cout << "Extern" << std::endl;
                    break;
                case Identifier:
                    std::cout << "Identifier " << t->get_value<std::string>() << std::endl;
                    break;
                case Nil:
                    std::cout << "NIL " << t->get_value<char>() << std::endl;
                    break;
                case Assignment:
                    std::cout << ":=" << std::endl;
                    break;
                case Colon:
                    std::cout << ":" << std::endl;
                    break;
                case Type:
                    std::cout << "Type" << std::endl;
                    break;
                case Str:
                    std::cout << "String " << t->get_value<std::string>() << std::endl;
                    break;
                case Bool:
                    std::cout << "Bool " << t->get_value<bool>() << std::endl;
                    break;
                case Char:
                    std::cout << "Char " << t->get_value<char>() << std::endl;
                    break;
                case Array:
                    std::cout << "Array " << std::endl;
                    break;
                case U8:
                    std::cout << "U8 " << t->get_value<u_int8_t>() << std::endl;
                    break;
                case U16:
                    std::cout << "U16 " << t->get_value<u_int16_t>() << std::endl;
                    break;
                case U32:
                    std::cout << "U32 " << t->get_value<u_int32_t>() << std::endl;
                    break;
                case U64:
                    std::cout << "U64 " << t->get_value<u_int64_t>() << std::endl;
                    break;
                case I8:
                    std::cout << "I8 " << t->get_value<int8_t>() << std::endl;
                    break;
                case I16:
                    std::cout << "I16 " << t->get_value<int16_t>() << std::endl;
                    break;
                case I32:
                    std::cout << "I32 " << t->get_value<int32_t>() << std::endl;
                    break;
                case I64:
                    std::cout << "I64 " << t->get_value<int64_t>() << std::endl;
                    break;
                case F32:
                    std::cout << "F32 " << t->get_value<float>() << std::endl;
                    break;
                case F64:
                    std::cout << "F64 " << t->get_value<double>() << std::endl;
                    break;
                default:
                    std::cout << "OTHER " << t->get_value<std::string>() << std::endl;
                    break;
            }
        }
}
