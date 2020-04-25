#include "calcx.h"

using namespace hgl::calc;


    double _calc_add(CalcFn::OprdList oprds);
    double _calc_sub(CalcFn::OprdList oprds);
    double _calc_mul(CalcFn::OprdList oprds);
    double _calc_div(CalcFn::OprdList oprds);
    double _calc_pow(CalcFn::OprdList oprds);
    double _calc_neg(CalcFn::OprdList oprds);


static const CalcFnPool builtin_calcfnpool = {
    {"+", {_calc_add, 2}},
    {"-", {_calc_sub, 2}},
    {"*", {_calc_mul, 2}},
    {"/", {_calc_div, 2}},
    {"^", {_calc_pow, 2}},
    {"~", {_calc_neg, 1}},
};

const CalcFnPool & hgl::calc::getBuiltinCalcFnPool()
{
    return builtin_calcfnpool;
}
