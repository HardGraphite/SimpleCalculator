#pragma once

#include <map>
#include <cstring>

namespace hgl
{
    namespace calc
    {
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

        struct _cstr_lt
        {
            bool operator()(const char * s1, const char * s2) const
                {return strcmp(s1, s2) < 0;}
        };

        using CalcFnPool = std::map<const char *, CalcFn, _cstr_lt>;

        const CalcFnPool & getBuiltinCalcFnPool();

    } // namespace calc
} // namespace hgl
