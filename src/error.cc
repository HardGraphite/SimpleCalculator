#include <error.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>

using namespace hgl::calc;


void Error::set_message(const char * msg)
{
    if (this->message)
        delete [] this->message;

    this->message = new char [std::strlen(msg) + 1];
    std::strcpy(this->message, msg);
}

void Error::delete_message()
{
    if (this->message == nullptr)
        return;

    delete [] this->message;
    this->message = nullptr;
}

Error::Error(Error && e)
{
    this->message = e.message;
    e.message = nullptr;
}

Error::Error(const Error & e): message(nullptr)
{
    *this = e;
}

Error::~Error()
{
    this->delete_message();
}


SyntaxError::SyntaxError(const char * fmt, ...): Error()
{
    va_list ap;
    char buffer[64];

    va_start(ap, fmt);
    std::vsnprintf(buffer, sizeof(buffer) - 1, fmt, ap);
    va_end(ap);

    this->set_message(buffer);
}
