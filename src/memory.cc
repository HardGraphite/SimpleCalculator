#include <mem.h>

using namespace hgl::calc;

Memory::Memory()
{
    this->emplace("pi", 3.141592653589793);
    this->emplace("e", 2.718281828459045);
}
