#include "lib.h"

int version()
{
    return PROJECT_VERSION_PATCH;
}

size_t factorial(size_t n)
{
    size_t result = 1;
    while(n > 1)
        result *= n--;
    return result;
}

