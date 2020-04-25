#pragma once


#include <cstdint>
#include <iostream>
#include <queue>
#include <string>


namespace hgl
{
    namespace calc
    {
        class Token
        {
            friend std::ostream & operator<<(std::ostream &, const Token &);

        public:
            using Number   = double;
            using Operator = char;
            using Symbol   = char[8];

            // token type
            enum class Type: std::uint8_t
            {
                Number,    // number, e.g. 1, -23.5, 2e3
                Operator,  // operator, e.g. +, *
                Symbol,    // symbol, e.g. and, sin
            };

        private:
            // token value
            union Value
            {
                Number   num;
                Operator opr;
                Symbol   sym;
            };

            Value   value;
            Type    type;

        public:
            Token() = delete;
            Token(Number x); // number
            Token(char x); // operator
            Token(const char * x); // symbol
            ~Token();

            // return token value
            Type getType() const noexcept
                {return this->type;}

            // get value as number
            Number asNumber() const noexcept
                {return this->value.num;}
            // get value as operator
            Operator asOperator() const noexcept
                {return this->value.opr;}
            // get value as symbol
            const char * asSymbol() const noexcept
                {return this->value.sym;}

            Token & operator=(const Token & t) noexcept;
            bool operator==(const Token & t) const noexcept;
            bool operator<(const Token & t) const noexcept;
        };


        class TokenStream: public std::queue<Token>
        {
        private:

        public:
            // put
            TokenStream & operator<<(const Token & t);
            TokenStream & operator<<(Token && t);
            // get
            TokenStream & operator>>(Token & t);
            Token get();

            friend std::ostream & operator<<(std::ostream &, const TokenStream &);
        };


        std::ostream & operator<<(std::ostream &, const Token &);
        std::ostream & operator<<(std::ostream &, const TokenStream &);

    } // namespace calc
} // namespace hgl
