#include <calculator.h>
#include <dlapi.h>

using namespace hgl::calc;


extern "C" void * calc_init(void)
{
    return (void*)(new Calculator);
}

extern "C" double calc_evaluate(void * calc, const char * expr)
{
    return ((Calculator*)calc)->calculate(expr);
}

extern "C" void calc_cleanup(void * calc)
{
    delete (Calculator*)calc;
}
