#pragma once

#include <calcfn.h>
#include <syntax.h>

namespace hgl
{
    namespace calc
    {
        double evaluate(const AST::Node &n, const CalcFnPool *cf = &BuiltinCalcFnPool);
        double evaluate(const AST &t, const CalcFnPool *cf = &BuiltinCalcFnPool);
    } // namespace calc
} // namespace hgl
