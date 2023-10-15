#include "math/math.h"

int32_t fixed_point_add(int32_t a, int32_t b)
{
    return a + b;
}

int32_t fixed_point_sub(int32_t a, int32_t b)
{
    return a - b;
}

int32_t fixed_point_mul(int32_t a, int32_t b)
{
    return (a * b) >> 14;
}

int32_t fixed_point_div(int32_t a, int32_t b)
{
    return (a << 14) / b;
}

int32_t fixed_point_to_int(int32_t a)
{
    return a >> 14;
}