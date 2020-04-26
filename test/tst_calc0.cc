#include <calculator.h>

using namespace hgl::calc;

static constexpr const char * exprs[] = {
    "1+1",
    "2+3*4",
    "-2*3",
    "2.5*4+6/(4.33-1.33)",
    "3.5^(-2)",
};

int main(int argc, char const *argv[])
{
    for (std::size_t i = 0; i < sizeof(exprs) / sizeof(exprs[0]); i++)
        std::cout << exprs[i] << " = " << calculate(exprs[i]) << '\n';

    return 0;
}
