
#include "../cub3d.h"

void	find_vector_values(t_vec *vec, double angle)
{
	if (angle > 0 && angle <= M_PI_2)
	{
		vec->x = 1.0;
		vec->y = tan(angle);
	}
	else if (angle > M_PI_2 && angle <= M_PI)
	{
		vec->x = -1.0;
		vec->y = tan(angle);
	}
	else if (angle > M_PI && angle <= 3 * M_PI_2)
	{
		vec->x = -1.0;
		vec->y = -tan(angle);
	}
	else if (angle > 3 * M_PI_2)
	{
		vec->x = 1.0;
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

void	perpendicular_vector(t_vec *vec)
{
	double	temp_x;
	double	temp_y;

	temp_x = vec->x;
	temp_y = vec->y;
	vec->y = -1.0 * temp_x;
	vec->x = temp_y;
}

void	calculate_distance(t_data *data)
{
	if (data->cur_ray->ori == 0)
		data->cur_ray->full_dist = \
		data->cur_ray->side_dist.x - data->cur_ray->delta_dist.x;
	else
		data->cur_ray->full_dist = \
		data->cur_ray->side_dist.y - data->cur_ray->delta_dist.y;
}
