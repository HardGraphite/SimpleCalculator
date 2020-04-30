#include <token.h>

#include <cstring>

using namespace hgl::calc;


Token::Token(Number x):
    value{.num = x}, type(Type::Number)
{}

Token::Token(char x):
    value{.opr = x}, type(Type::Operator)
{}

Token::Token(const char * x):
    type(Type::Symbol)
{
    std::strncpy(this->value.sym, x, 7);
    this->value.sym[std::strlen(x)] = '\0';
}

Token::~Token()
{
}


Token & Token::operator=(const Token & t) noexcept
{
    if (this->type != t.type)
    {
        this->~Token();
        this->type = t.type;
    }

    switch (this->type)
    {
    case Type::Number :
        this->value.num = t.value.num;
        break;

    case Type::Operator :
        this->value.opr = t.value.opr;
        break;

    case Type::Symbol :
        std::strcpy(this->value.sym, t.value.sym);
        break;
    }

    return *this;
}

bool Token::operator==(const Token & t) const noexcept
{
    if (this->type != t.type)
        return false;

    bool is_eq;

    switch (this->type)
    {
    case Type::Number :
        is_eq = this->value.num == t.value.num;
        break;

    case Type::Operator :
        is_eq = this->value.opr == t.value.opr;
        break;

    case Type::Symbol :
        is_eq = std::strncmp(this->value.sym, t.value.sym, 7) == 0;
        break;
    }

    return is_eq;
}

bool Token::operator==(Number n) const noexcept
{
    if (this->type != Type::Number)
        return false;
    else
        return this->value.num == n;
}

bool Token::operator==(Operator o) const noexcept
{

    if (this->type != Type::Operator)
        return false;
    else
        return this->value.opr == o;
}

bool Token::operator==(const char * s) const noexcept
{

    if (this->type != Type::Symbol)
        return false;
    else
        return std::strncmp(this->value.sym, s, 7);
}

bool Token::operator!=(const Token & t) const noexcept
{
    if (this->type != t.type)
        return true;

    bool is_eq;

    switch (this->type)
    {
    case Type::Number :
        is_eq = this->value.num != t.value.num;
        break;

    case Type::Operator :
        is_eq = this->value.opr != t.value.opr;
        break;

    case Type::Symbol :
        is_eq = std::strncmp(this->value.sym, t.value.sym, 7) != 0;
        break;
    }

    return is_eq;
}

bool Token::operator<(const Token & t) const noexcept
{
    bool is_lt;

    switch (this->type)
    {
    case Type::Number :
        is_lt = this->value.num < t.value.num;
        break;

    case Type::Operator :
        is_lt = this->value.opr < t.value.opr;
        break;

    case Type::Symbol :
        is_lt = std::strncmp(this->value.sym, t.value.sym, 8) < 0;
        break;

    default:
        is_lt = false;
        break;
    }

    return is_lt;
}


std::ostream & hgl::calc::operator<<(std::ostream & os, const Token & t)
{

    switch (t.type)
    {
    case Token::Type::Number :
        os << "<Number: “" << t.value.num << "”>";
        break;

    case Token::Type::Operator :
        os << "<Operator: “" << t.value.opr << "”>";
        break;

    case Token::Type::Symbol :
        os << "<Symbol: “" << t.value.sym << "”>";
        break;

    default:
        os << "<?>";
        break;
    }


    /* switch (t.type)
    {
    case Token::Type::Number :
        os << t.value.num;
        break;

    case Token::Type::Operator :
        os << t.value.opr;
        break;

    case Token::Type::Symbol :
        os << t.value.sym;
        break;

    default:
        os << "<?>";
        break;
    } */

    return os;
}
