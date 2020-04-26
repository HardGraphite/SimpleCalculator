#include <calcfn.h>
#include <cmath>

using namespace hgl::calc;

// e^n
double _calc_exp(CalcFn::OprdList oprds)
{
    return std::exp(oprds[0]);
}

// 2^n
double _calc_exp2(CalcFn::OprdList oprds)
{
    return std::exp2(oprds[0]);
}

