#include <calculator.h>
#include <sstream>
#include <iostream>

using namespace hgl::calc;


int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: no input expr!\n"
            << "Usage: " << argv[0] << " <EXPR>\n"
            << "Example: " << argv[0] << "  4 ^ (3 + 2 - 1) * 5\n";
        return EXIT_FAILURE;
    }

    std::stringstream ss;

    for (int i = 1; i < argc; i++)
        ss << ' ' << argv[i] << ' ';

    std::cout << ss.str() << " = " << calculate(ss) << std::endl;

    return 0;
}
