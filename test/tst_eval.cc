#include <calculator.h>

using namespace hgl::calc;

int main(int argc, char const *argv[])
{
    if (argc < 2)
        return 1;

    std::cout << calculate(argv[1]) << '\n';

    return 0;
}
