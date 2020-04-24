#pragma once

#include <syntax.h>

namespace hgl
{
    namespace calc
    {
        double evaluate(const AST::Node & n);
        double evaluate(const AST & t);
    } // namespace calc
} // namespace hgl
