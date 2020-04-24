#pragma once

#include <iostream>

namespace hgl
{
    namespace calc
    {
        double calculate(const char * expr);
        double calculate(std::istream & expr);
    } // namespace calc
} // namespace hgl
