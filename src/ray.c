
#include "../cub3d.h"

void	cast_ray(t_data *data)
{
	t_ray	ray;
	int		i;
	float	atan;

	ray.done = false;
	ray.x = data->pos.x;
	ray.y = data->pos.y;
	i = 1;
	while (ray.done == false)
	{
		while (i > 0)
		{
			ray.dir_x = data->dir.x;
			ray.dir_y = data->dir.y;
			ray.angle = atan2(ray.dir_y, ray.dir_x);
			// ---- check horizontal lines ---- //
			atan = - 1 / tan(ray.angle);
			if (ray.angle < M_PI) // the ray is looking up
			{
				ray.y = ceil(data->pos.y / 72.0) * 72.0;
				draw_point(72, ray.y, data);
			}
		}
	}
}
