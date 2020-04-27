#include <calculator.h>

using namespace hgl::calc;

static constexpr const char * exprs[] = {
    "num=sin($pi/2)",
    "cbrt($num*$e)",
};

int main(int argc, char const *argv[])
{
    Calculator c;

    for (std::size_t i = 0; i < sizeof(exprs) / sizeof(exprs[0]); i++)
        std::cout << exprs[i] << " = " << c.calculate(exprs[i]) << '\n';

    return 0;
}
