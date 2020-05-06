#include <calculator.h>
#include <cmath>

using namespace hgl::calc;

static constexpr const char * exprs[] = {
    "rand(100)",
};

double fn_rand(double args[])
{
    int x_max = args[0];
    return std::rand() % x_max;
}

int main(int argc, char const *argv[])
{
    Calculator c;

    c.add_function("rand", {fn_rand, 1});

    for (std::size_t i = 0; i < sizeof(exprs) / sizeof(exprs[0]); i++)
        std::cout << exprs[i] << " = " << c.calculate(exprs[i]) << '\n';

    return 0;
}
