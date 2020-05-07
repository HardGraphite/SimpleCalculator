#pragma once

#include <error.h>

#include <map>
#include <memory>
#include <string>

namespace hgl
{
    namespace calc
    {
        class Memory: public std::map<std::string, double>
        {
        public:
            Memory();

            void setValue(const char * name, double value)
            {
                map::operator[](name) = value;
            }

            double operator[] (const char * n) const
            {
                auto iter = this->find(n);
                if (iter == this->end())
                    throw SyntaxError("undefined name: '%s'", n);
                else
                    return iter->second;
            }
        };
    } // namespace calc
} // namespace hgl
