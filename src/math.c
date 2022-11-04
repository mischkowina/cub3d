
#include "../cub3d.h"

void	find_vector_values(t_vec *vec, double angle)
{
	if (angle > 0 && angle <= M_PI / 2)
	{
		vec->x = 1;
		vec->y = tan(angle);
	}
	else if (angle > M_PI / 2 && angle <= M_PI)
	{
		vec->x = -1;
		vec->y = tan(angle);
	}
	else if (angle > M_PI && angle <= 3 * M_PI / 2)
	{
		vec->x = -1;
		vec->y = -tan(angle);
	}
	else if (angle > 3 * M_PI / 2)
	{
		vec->x = 1;
		vec->y = -tan(angle);
	}
}

void	normalize_vector(t_vec *vec)
{
	double	length;

	length = sqrt((vec->x * vec->x) + (vec->y * vec->y));
	vec->x /= length;
	vec->y /= length;
}