#pragma once

#include <token.h>

#include <iostream>
#include <sstream>


namespace hgl
{
    namespace calc
    {
        class Scanner
        {
        private:
            enum Status
            {
                Idle = 0,
                RdNumber,
                RdLetter,
                // RdOperator,
            };

            std::stringstream buffer;
            Status            status;

        public:
            // scan input string and generate tokens
            TokenStream scan(std::istream & in);
        };

    } // namespace calc
} // namespace hgl
