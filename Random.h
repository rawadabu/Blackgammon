#ifndef RANDOMINT_H_
#define RANDOMINT_H_

class customRandom
{
private:
    unsigned int x;

public:
    customRandom() : x(0){};
    customRandom(unsigned int seed) : x(seed){};
    unsigned int get_rand();
};

#endif
