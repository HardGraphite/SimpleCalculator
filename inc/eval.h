#pragma once

#include <calcfn.h>
#include <mem.h>
#include <syntax.h>

namespace hgl
{
    namespace calc
    {
        double evaluate(const AST::Node &n,
            const CalcFnPool *cf = &BuiltinCalcFnPool, Memory * m = nullptr);

        double evaluate(const AST &t,
            const CalcFnPool *cf = &BuiltinCalcFnPool, Memory * m = nullptr);
    } // namespace calc
} // namespace hgl
