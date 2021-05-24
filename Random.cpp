#include "Random.h"

unsigned int customRandom::get_rand()
{
    const unsigned int a = 22695477;
    const unsigned int c = 1;
    x = a * x + c;
    return (x & 0x7fffffff) >> 16;
}
