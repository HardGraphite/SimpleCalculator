#include <lexic.h>
#include <syntax.h>
#include <eval.h>
#include <calculator.h>

#include <sstream>

using namespace hgl::calc;


double hgl::calc::calculate(const char * expr)
{
    std::stringstream ss;
    ss.str(expr);
    return calculate(ss);
}

double hgl::calc::calculate(std::istream & expr)
{
    Scanner scanner;
    Parser parser;

    return evaluate(parser.parse(scanner.scan(expr)));
}
