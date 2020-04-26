#include <calcfn.h>
#include <cmath>

using namespace hgl::calc;


double _calc_pow(CalcFn::OprdList oprds)
{
    return std::pow(oprds[0], oprds[1]);
}

double _calc_sqrt(CalcFn::OprdList oprds)
{
    return std::sqrt(oprds[0]);
}

double _calc_cbrt(CalcFn::OprdList oprds)
{
    return std::cbrt(oprds[0]);
}
