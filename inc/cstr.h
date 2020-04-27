#pragma once

#include <cstring>

namespace hgl
{
    namespace calc
    {
        template <typename _T> struct less
        {
            bool operator()(const _T & a, const _T & b) const
                {return a < b;}
        };

        template < > struct less<const char*>
        {
            bool operator()(const char * a, const char * b) const
                {return std::strcmp(a, b) < 0;}
        };
    } // namespace calc
} // namespace hgl
