#include <calcfn.h>
#include <cmath>

using namespace hgl::calc;

double _calc_log10(CalcFn::OprdList oprds)
{
    return std::log10(oprds[0]);
}

double _calc_log2(CalcFn::OprdList oprds)
{
    return std::log2(oprds[0]);
}

double _calc_ln(CalcFn::OprdList oprds)
{
    return std::log(oprds[0]);
}

double _calc_log(CalcFn::OprdList oprds)
{
    return std::log(oprds[0]) / std::log(oprds[1]);
}
