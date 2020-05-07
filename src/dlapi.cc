#include <calculator.h>
#include <dlapi.h>

#include <cstring>
#include <cstdio>

using namespace hgl::calc;


static void print_exception(const std::exception & e)
{
    std::cerr << "calc: " << e.what() << std::endl;
}


extern "C" void * calc_init(void)
{
    try
    {
        return (void*)(new Calculator);
    }
    catch (const std::exception & e)
    {
        print_exception(e);
        std::abort();
    }
}

extern "C" double calc_evaluate(void * calc, const char * expr)
{
    try
    {
        return ((Calculator*)calc)->calculate(expr);
    }
    catch (const std::exception & e)
    {
        print_exception(e);
        std::abort();
    }
}

extern "C" double
calc_try_evaluate(void * calc, const char * expr, char * errstr, int errlen)
{
    try
    {
        auto res = ((Calculator*)calc)->calculate(expr);
        errstr[0] = '\0';
        return res;
    }
    catch (const SyntaxError & e)
    {
        std::snprintf(errstr, errlen - 1, "SyntaxError: %s", e.what());
        return 0;
    }
    catch (const std::exception & e)
    {
        print_exception(e);
        std::abort();
    }
}

extern "C" void calc_cleanup(void * calc)
{
    try
    {
        delete (Calculator*)calc;
    }
    catch (const std::exception & e)
    {
        print_exception(e);
        std::abort();
    }
}
