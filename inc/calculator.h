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
        // evaluate an expression
        double calculate(const char * expr);
        // evaluate an expression
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

            // evaluate an expression
            double calculate(const char * expr);
            // evaluate an expression
            double calculate(std::istream & expr);

            // add calculation function
            void add_function(const char * name, const CalcFn & fn);
        };

    } // namespace calc
} // namespace hgl
