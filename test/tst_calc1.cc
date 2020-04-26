#include <calculator.h>

using namespace hgl::calc;

static constexpr const char * exprs[] = {
    "add(1 2)",
    "add(1, 2)",
    "exp2((1 + 2) * 3)",
    "log((1000 / 2 + 12), 2)"
};

int main(int argc, char const *argv[])
{
    for (std::size_t i = 0; i < sizeof(exprs) / sizeof(exprs[0]); i++)
        std::cout << exprs[i] << " = " << calculate(exprs[i]) << '\n';

    return 0;
}
