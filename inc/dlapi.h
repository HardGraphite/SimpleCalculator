#pragma once


extern "C"
{
    void * calc_init(void);
    double calc_evaluate(void * calc, const char * expr);
    double calc_try_evaluate(void * calc, const char * expr, char * errstr, int errlen);
    void calc_cleanup(void * calc);
}
