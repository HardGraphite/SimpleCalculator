#include <lexic.h>

using namespace hgl::calc;

int main(int argc, char const *argv[])
{
    if (argc < 2)
        return 1;

    std::stringstream ss;
    ss.str(argv[1]);

    Scanner scanner;
    auto tokens = scanner.scan(ss);

    std::cout << tokens << '\n';

    return 0;
}
