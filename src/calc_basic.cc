#include "calcx.h"
#include <cmath>

using namespace hgl::calc;

double _calc_add(CalcFn::OprdList oprds)
{
    return oprds[0] + oprds[1];
}

double _calc_sub(CalcFn::OprdList oprds)
{
    return oprds[0] - oprds[1];
}

double _calc_mul(CalcFn::OprdList oprds)
{
    return oprds[0] * oprds[1];
}

double _calc_div(CalcFn::OprdList oprds)
{
    return oprds[0] / oprds[1];
}

double _calc_pow(CalcFn::OprdList oprds)
{
    return std::pow(oprds[0], oprds[1]);
}

