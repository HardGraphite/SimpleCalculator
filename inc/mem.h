#pragma once

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
                    throw std::runtime_error("cannot find the value");
                else
                    return iter->second;
            }
        };
    } // namespace calc
} // namespace hgl
