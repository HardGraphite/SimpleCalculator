#pragma once

#include <exception>

namespace hgl
{
    namespace calc
    {
        class Error: public std::exception
        {
        protected:
            char * message;
            void set_message(const char * msg);
            void delete_message();

        public:
            Error(): message(nullptr) {}
            Error(Error && e);
            Error(const Error & e);
            ~Error();

            Error & operator=(const Error & e)
                {this->set_message(e.message); return *this;}

            virtual const char * what() const noexcept
                {return this->message;}
        };


        class SyntaxError final: public Error
        {
        public:
            SyntaxError(const char * fmt, ...);
            using Error::Error;
        };


        class FatalError final: public Error
        {
        public:
            FatalError(const char * msg): Error()
                {this->set_message(msg);}
            using Error::Error;
        };
    } // namespace calc
} // namespace hgl
