#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <unordered_map>

enum class TokenType { exit, int_lit, semi, open_paren, close_paren, ident, set, eq, plus, star, sub, div, open_curl, close_curl,if_,elif,else_,for_,greater,lesser};


inline std::ostream& operator<<(std::ostream& os, TokenType type) {
    static const std::unordered_map<TokenType, std::string> token_type_strings = {
            {TokenType::exit, "exit"}, {TokenType::int_lit, "int_lit"}, {TokenType::semi, "semi"},
            {TokenType::open_paren, "open_paren"}, {TokenType::close_paren, "close_paren"},
            {TokenType::ident, "ident"}, {TokenType::set, "set"}, {TokenType::eq, "eq"},
            {TokenType::plus, "plus"}, {TokenType::star, "star"}, {TokenType::sub, "sub"},
            {TokenType::div, "div"}, {TokenType::open_curl, "open_curl"}, {TokenType::close_curl, "close_curl"},
            {TokenType::if_, "if"}, {TokenType::elif, "elif"}, {TokenType::else_, "else"},
            {TokenType::for_, "for"}, {TokenType::greater, "greater"}, {TokenType::lesser, "lesser"}
    };

    return os << token_type_strings.at(type);
}

inline std::optional<int> bin_prec(const TokenType type)
{
    switch (type) {
        case TokenType::sub:
        case TokenType::plus:
            return 0;
        case TokenType::div:
        case TokenType::star:
            return 1;

        default:
            return {};
    }
}

inline std::optional<int> bin_prec_con(const TokenType type)
{
    switch (type) {
        case TokenType::greater:
        case TokenType::lesser:
        case TokenType::eq:
            return 0;
        default:
            return {};
    }
}

inline std::string to_string(const TokenType type)
{
    switch (type) {
        case TokenType::exit:
            return "`exit`";
        case TokenType::int_lit:
            return "int literal";
        case TokenType::semi:
            return "`;`";
        case TokenType::open_paren:
            return "`(`";
        case TokenType::close_paren:
            return "`)`";
        case TokenType::ident:
            return "identifier";
        case TokenType::set:
            return "`let`";
        case TokenType::eq:
            return "`=`";
        case TokenType::plus:
            return "`+`";
        case TokenType::star:
            return "`*`";
        case TokenType::sub:
            return "`-`";
        case TokenType::div:
            return "`/`";
        case TokenType::open_curl:
            return "`{`";
        case TokenType::close_curl:
            return "`}`";
        case TokenType::if_:
            return "`if`";
        case TokenType::elif:
            return "`elif`";
        case TokenType::else_:
            return "`else`";
        case TokenType::for_:
            return "`else`";
        case TokenType::greater:
            return "`else`";
        case TokenType::lesser:
            return "`else`";
    }
    assert(false);
}


struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};

class Tokenizer {
public:
    inline explicit Tokenizer(std::string src)
            : m_src(std::move(src))
    {
    }

    inline std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf;
        int line_count =1;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit") {
                    tokens.push_back({ TokenType::exit,line_count });
                    buf.clear();
                }
                else if (buf == "set") {
                    tokens.push_back({ TokenType::set,line_count });
                    buf.clear();
                }
                else if (buf == "if") {
                    tokens.push_back({ TokenType::if_,line_count });
                    buf.clear();
                }
                else if (buf == "elif")
                {
                    tokens.push_back({ TokenType::elif,line_count });
                    buf.clear();
                }
                else if (buf == "else")
                {
                    tokens.push_back({ TokenType::else_,line_count });
                    buf.clear();
                }
                else if (buf == "for")
                {
                    tokens.push_back({ TokenType::for_,line_count });
                    buf.clear();
                }
                else {
                    tokens.push_back({ TokenType::ident,line_count,buf });
                    buf.clear();
                }
            }
            else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({ .type = TokenType::int_lit, .value = buf });
                buf.clear();
            }

            else if (peek().value() == '!' && peek(1).has_value() && peek(1).value() == '!')
            {
                consume();
                consume();
                while (peek().has_value() && peek().value() !='\n')
                {
                    consume();
                }
            }

            else if (peek().value() == '!' && peek(1).has_value() && peek(1).value() == '*')
            {
                consume();
                consume();
                while (peek().has_value())
                {
                    if(peek().value() =='*' && peek(1).has_value() && peek(1).value()=='!')
                    {
                        break;
                    }
                    consume();
                }
                if(peek().has_value())
                {
                    consume();
                }
                if(peek().has_value())
                {
                    consume();
                }
            }


            else if (peek().value() == '(') {
                consume();
                tokens.push_back({ TokenType::open_paren,line_count });
            }
            else if (peek().value() == ')') {
                consume();
                tokens.push_back({ TokenType::close_paren,line_count });
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push_back({ TokenType::semi,line_count });
            }
            else if (peek().value() == '=') {
                consume();
                tokens.push_back({ TokenType::eq,line_count });
            }
            else if (peek().value() == '+') {
                consume();
                tokens.push_back({ TokenType::plus,line_count });
            }
            else if (peek().value() == '*') {
                consume();
                tokens.push_back({ TokenType::star,line_count });
            }
            else if (peek().value() == '-') {
                consume();
                tokens.push_back({ TokenType::sub,line_count });
            }
            else if (peek().value() == '/') {
                consume();
                tokens.push_back({ TokenType::div,line_count });
            }
            else if (peek().value() == '{') {
                consume();
                tokens.push_back({ TokenType::open_curl,line_count });
            }
            else if (peek().value() == '}') {
                consume();
                tokens.push_back({ TokenType::close_curl,line_count});
            }
            else if (peek().value() == '>') {
                consume();
                tokens.push_back({ TokenType::greater,line_count});
            }
            else if (peek().value() == '<') {
                consume();
                tokens.push_back({ TokenType::lesser,line_count});
            }
            else if (peek().value() == '\n') {
                consume();
                line_count++;
            }
            else if (std::isspace(peek().value())) {
                consume();
            }
            else {
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] std::optional<char> peek(int offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index + offset);
    }

    char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};