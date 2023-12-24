#include "others.h"

long long gettime()
{
    auto now=system_clock::now();
    auto millsec=duration_cast<milliseconds>(now.time_since_epoch()).count();
    return millsec;
}

int Get_2_N_POW(int num)
{
    int res = -1;
    while (num)
    {
        num >>=1;
        res++;
    }
    return res;
}

void Random::SetSeed(int seed)
{
    srand(seed);
}

int Random::rand(int begin, int end)
{
    return begin + (::rand() % (end - begin));
}

