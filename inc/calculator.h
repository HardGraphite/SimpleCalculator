#pragma once

#include <calcfn.h>
#include <lexic.h>
#include <mem.h>
#include <syntax.h>

#include <iostream>

namespace hgl
{
    namespace calc
    {
        double calculate(const char * expr);
        double calculate(std::istream & expr);


        class Calculator
        {
        private:
            CalcFnPool  cfnpool;
            Memory      memory;
            Scanner     scanner;
            Parser      parser;

        public:
            Calculator();
            Calculator(const CalcFnPool && calcfnpool);

            double calculate(const char * expr);
            double calculate(std::istream & expr);
        };

    } // namespace calc
} // namespace hgl
