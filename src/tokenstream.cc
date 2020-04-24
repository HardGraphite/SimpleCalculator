#include <token.h>

using namespace hgl::calc;


TokenStream & TokenStream::operator<<(const Token & t)
{
    this->push(t);
    return *this;
}

TokenStream & TokenStream::operator<<(Token && t)
{
    this->push(std::move(t));
    return *this;
}

TokenStream & TokenStream::operator>>(Token & t)
{
    t = this->front();
    this->pop();
    return *this;
}

Token TokenStream::get()
{
    Token out(this->front());
    this->pop();
    return out;
}


std::ostream & hgl::calc::operator<<(std::ostream & os, const TokenStream & s)
{
    auto s_cp = s;

    os << '[';
    while (!s_cp.empty())
        os << s_cp.get() << ", ";
    os << ']';

    return os;
}
