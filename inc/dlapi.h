#pragma once


extern "C"
{
    void * calc_init(void);
    double calc_evaluate(void * calc, const char * expr);
    void calc_cleanup(void * calc);
}
