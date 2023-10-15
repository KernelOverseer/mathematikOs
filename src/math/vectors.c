#include "math/math.h"
#define MINDIFF 2.25e-308                   // use for convergence check
#define n 20

vector vector_add(vector a, vector b)
{
    vector c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

vector vector_sub(vector a, vector b)
{
    vector c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}


double sqrt(double square)
{
    double root=square/3, last, diff=1;
    if (square <= 0) return 0;
    do {
        last = root;
        root = (root + square / root) / 2;
        diff = root - last;
    } while (diff > MINDIFF || diff < -MINDIFF);
    return root;
}

vector vector_normalize(vector a)
{
    vector c;
    float length = sqrt(a.x * a.x + a.y * a.y);
    c.x = a.x / length;
    c.y = a.y / length;
    return c;
}

double sin(double x) // sin calculation
{
    double sum;
    double fa;
    double pow;
    sum = 0.0;
    for (int i = 0; i <= n; i++)
    {
        fa = 1.0;
        pow = 1.0;
        for (int j = 1; j <= 2 * i + 1; j++)
        {
            fa *= j;
            pow *= x;
        }
        sum += ((i % 2 ? -1.0 : 1.0) / fa) * pow;
    }
    return sum;
}

double cos(double x) // cosine calculation
{
    double sum;
    double fa;
    double pow;
    sum = 0.0;
    for (int i = 0; i <= n; i++)
    {
        fa = 1.0;
        pow = 1.0;
        for (int j = 1; j <= 2 * i; j++)
        {
            fa *= j;
            pow *= x;
        }
        sum += ((i % 2 ? -1.0 : 1.0) / fa) * pow;
    }
    return sum;
}

vector get_vector_from_angle(float angle)
{
    vector c;
    c.x = cos(angle);
    c.y = sin(angle);
    return c;
}

vector vector_mul(vector a, float b)
{
    vector c;
    c.x = a.x * b;
    c.y = a.y * b;
    return c;
}

vector vector_create(float x, float y)
{
    vector c;
    c.x = x;
    c.y = y;
    return c;
}

typedef struct          s_intercalc
{
    vector            p1;
    vector            p2;
    vector            p3;
    vector            p4;
    double              den;
    double              u;
    double              t;
}                       t_intercalc;

float vector_distance(vector a, vector b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float vector_size(vector a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

static void	ft_point_vector(vector p, vector *r1, vector p2, vector *r2)
{
	r1->x = p.x;
	r1->y = p.y;
	r2->x = p2.x;
	r2->y = p2.y;
}

vector  ft_intersect(vector ray_origin, vector ray_direction, vector wall_p0, vector wall_p1, int *status)
{
	t_intercalc	c;

	*status = 0;
	c.p1 = (vector){ray_origin.x, ray_origin.y};
	c.p2 = (vector){c.p1.x + ray_direction.x, c.p1.y + ray_direction.y};
	ft_point_vector(wall_p0, &c.p3, wall_p1, &c.p4);
	c.den = ((c.p1.x - c.p2.x) * (c.p3.y - c.p4.y) - (c.p1.y - c.p2.y) *
			(c.p3.x - c.p4.x));
	if (c.den == 0)
		return ((vector){0,0});
	c.t = ((c.p1.x - c.p3.x) * (c.p3.y - c.p4.y) - (c.p1.y - c.p3.y) *
			(c.p3.x - c.p4.x)) / c.den;
	if (c.t < 0)
		return ((vector){0,0});
	c.u = -((c.p1.x - c.p2.x) * (c.p1.y - c.p3.y) - (c.p1.y - c.p2.y) *
			(c.p1.x - c.p3.x)) / c.den;
	if (c.u < 0 || c.u > 1)
		return ((vector){0,0});
	*status = 1;
	return ((vector){c.p1.x + c.t * (c.p2.x - c.p1.x), c.p1.y +
				c.t * (c.p2.y - c.p1.y)});
}