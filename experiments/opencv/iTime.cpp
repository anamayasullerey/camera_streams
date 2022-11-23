#include "iTime.hpp"
#include <time.h>

uint64_t itime_get_us()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
}

