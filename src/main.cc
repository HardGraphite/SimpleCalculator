#include <calculator.h>
#include <iostream>
#include <sstream>

#ifndef USE_READLINE
#   define USE_READLINE true
#endif

#if USE_READLINE
#   include <readline/readline.h>
#   include <readline/history.h>
#endif

using namespace hgl::calc;


int main(int argc, char const *argv[])
{
    if (argc == 1) // shell
    {
        Calculator calculator;

        while (!std::cin.eof())
        {
#if USE_READLINE
            auto line = readline("> ");
            if (line == nullptr)
                break;
            if (line[0] == '\0')
                continue;
            add_history(line);
            auto result = calculator.calculate(line);
            std::free(line);
            std::cout << "\t = " << result << std::endl;
#else
            std::cout << "> " << std::flush;
            char linebuffer[256];
            std::cin.getline(linebuffer, 255);
            if (linebuffer[0] == '\0')
                continue;
            auto result = calculator.calculate(linebuffer);
            std::cout << "\t = " << result << std::endl;
#endif // USE_READLINE
        }
    }
    else if (argc == 2 && std::strcmp(argv[1], "-") == 0) // read from stdin
    {
        Calculator calculator;
        char linebuffer[256];

        while (!std::cin.eof())
        {
            std::cin.getline(linebuffer, 255);
            if (linebuffer[0] == '\0')
                continue;
            auto result = calculator.calculate(linebuffer);
            std::cout << result << std::endl;
        }
    }
    else // read from cmdline args
    {
        std::stringstream ss;

        for (int i = 1; i < argc; i++)
            ss << ' ' << argv[i] << ' ';

        std::cout << ss.str() << " = " << calculate(ss) << std::endl;
    }

    return 0;
}
