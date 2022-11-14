
#include "../cub3d.h"

void	cast_ray(t_data *data)
{
	t_ray	ray;
	int		grid;

	ray.done = false;
	ray.x = data->pos.x;
	ray.y = data->pos.y;
	grid = 1;
	while (ray.done == false)
	{
		while (grid > 0)
		{
			ray.dir_x = data->dir.x;
			ray.dir_y = data->dir.y;
			ray.angle = atan2(ray.dir_y, ray.dir_x);
			if (ray.angle >= 0 && ray.angle < 90) // the ray is looking up and right
		}
	}
}
