#ifndef MATH_H
#define MATH_H
#include <stdint.h>
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

int32_t fixed_point_add(int32_t a, int32_t b);
int32_t fixed_point_sub(int32_t a, int32_t b);
int32_t fixed_point_mul(int32_t a, int32_t b);
int32_t fixed_point_div(int32_t a, int32_t b);
int32_t fixed_point_to_int(int32_t a);

typedef struct s_vector
{
    float x;
    float y;
} vector;

double sqrt(double x);
double cos(double x);
double sin(double x);
vector vector_add(vector a, vector b);
vector vector_sub(vector a, vector b);
vector vector_normalize(vector a);
vector get_vector_from_angle(float angle);
vector vector_mul(vector a, float b);
vector vector_create(float x, float y);
float vector_size(vector a);
float vector_distance(vector a, vector b);
vector  ft_intersect(vector ray_origin, vector ray_direction, vector wall_p0, vector wall_p1, int *status);

#endif