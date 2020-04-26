#include <calcfn.h>

using namespace hgl::calc;


    double _calc_add(CalcFn::OprdList oprds);
    double _calc_sub(CalcFn::OprdList oprds);
    double _calc_mul(CalcFn::OprdList oprds);
    double _calc_div(CalcFn::OprdList oprds);
    double _calc_neg(CalcFn::OprdList oprds);

    double _calc_log10(CalcFn::OprdList oprds);
    double _calc_log2(CalcFn::OprdList oprds);
    double _calc_ln(CalcFn::OprdList oprds);
    double _calc_log(CalcFn::OprdList oprds);

    double _calc_exp(CalcFn::OprdList oprds);
    double _calc_exp2(CalcFn::OprdList oprds);

    double _calc_pow(CalcFn::OprdList oprds);
    double _calc_sqrt(CalcFn::OprdList oprds);
    double _calc_cbrt(CalcFn::OprdList oprds);

    double _calc_sin(CalcFn::OprdList oprds);
    double _calc_cos(CalcFn::OprdList oprds);
    double _calc_tan(CalcFn::OprdList oprds);
    double _calc_asin(CalcFn::OprdList oprds);
    double _calc_acos(CalcFn::OprdList oprds);
    double _calc_atan(CalcFn::OprdList oprds);


const CalcFnPool hgl::calc::BuiltinCalcFnPool = {
    {"+", {_calc_add, 2}},
    {"-", {_calc_sub, 2}},
    {"*", {_calc_mul, 2}},
    {"/", {_calc_div, 2}},
    {"^", {_calc_pow, 2}},
    {"~", {_calc_neg, 1}},
    {"add", {_calc_add, 2}},
    {"sub", {_calc_sub, 2}},
    {"mul", {_calc_mul, 2}},
    {"div", {_calc_div, 2}},
    {"pow", {_calc_pow, 2}},
    {"neg", {_calc_neg, 1}},

    {"log10", {_calc_log10, 1}},
    {"log2",  {_calc_log2,  1}},
    {"ln",    {_calc_ln,    1}},
    {"log",   {_calc_log,   2}},

    {"exp",  {_calc_exp,  1}},
    {"exp2", {_calc_exp2, 1}},

    {"sqrt", {_calc_sqrt, 1}},
    {"cbrt", {_calc_cbrt, 1}},

    {"sin", {_calc_sin, 1}},
    {"cos", {_calc_cos, 1}},
    {"tan", {_calc_tan, 1}},
    {"asin", {_calc_asin, 1}},
    {"acos", {_calc_acos, 1}},
    {"atan", {_calc_atan, 1}},
};
