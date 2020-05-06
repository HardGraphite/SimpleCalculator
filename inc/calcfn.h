#pragma once

#include <cstr.h>

#include <map>

namespace hgl
{
    namespace calc
    {
        // calculate function
        struct CalcFn
        {
            using OprdList = double[];
            using Function = double (*) (OprdList);

            Function handle;
            unsigned oprdn;

            double operator() (OprdList oprds, unsigned int oprdn) const
            {
                if (this->oprdn != oprdn)
                    throw std::runtime_error("unmatched oprdn");
                return (this->handle)(oprds);
            }
        };

        // calculate function pool
        class CalcFnPool: public std::map<const char *, CalcFn, less<const char*> >
        {
        private:
            const CalcFnPool * inherit;

        public:
            CalcFnPool(const CalcFnPool * inherit = nullptr):
                map(), inherit(inherit) {}
            CalcFnPool(std::initializer_list<value_type> _l):
                map(_l), inherit(nullptr) {}

            const CalcFn & operator[] (const char * n) const
            {
                auto iter = this->find(n);
                if (iter == this->end())
                {
                    if (this->inherit != nullptr)
                        return (*this->inherit)[n];
                    else
                        throw std::runtime_error("cannot find the function");
                }
                else
                    return iter->second;
            }

            const CalcFn & operator[] (char n) const
            {
                char name[2] = {n, '\0'};
                return (*this)[name];
            }
        };

        // builtin CalcFnPool
        extern const CalcFnPool BuiltinCalcFnPool;

    } // namespace calc
} // namespace hgl
