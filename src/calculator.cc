#include <lexic.h>
#include <syntax.h>
#include <eval.h>
#include <calculator.h>

#include <sstream>

using namespace hgl::calc;


double hgl::calc::calculate(const char * expr)
{
    Calculator c;
    return c.calculate(expr);
}

double hgl::calc::calculate(std::istream & expr)
{
    Calculator c;
    return c.calculate(expr);
}


Calculator::Calculator():
    cfnpool(&BuiltinCalcFnPool)
{
}

Calculator::Calculator(const CalcFnPool && calcfnpool):
    cfnpool(std::move(calcfnpool))
{
}

double Calculator::calculate(const char * expr)
{
    std::stringstream ss;
    ss.str(expr);
    return this->calculate(ss);
}

double Calculator::calculate(std::istream & expr)
{
    auto ans = evaluate(
        this->parser.parse(this->scanner.scan(expr)),
        &this->cfnpool,
        &this->memory
    );

    this->memory.setValue("ans", ans);

    return ans;
}
