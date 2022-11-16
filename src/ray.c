
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
			if (ray.angle < 0)
				ray.angle *= -1;
			else if (ray.angle > 0) //&& ray.angle > M_PI / 2)
				ray.angle = M_PI - ray.angle + M_PI;

			// ---- check horizontal lines ---- //
			atan = - 1 / tan(ray.angle);
			printf(">>> this is the angle: %f\n", ray.angle * 180 / M_PI);
			if (ray.angle < M_PI) // the ray is looking up
			{
				ray.y = floor(data->pos.y / 72.0) * 72.0;
				printf("ray.y: %f\n", ray.y);
				draw_point(72, ray.y, data, RED);
			}
			else if (ray.angle > M_PI) // the ray is looking down
			{
				ray.y = ceil(data->pos.y / 72.0) * 72.0;
				printf("ray.y: %f\n", ray.y);
				draw_point(72, ray.y, data, GREEN);
			}

			// |||| check vertical lines |||| //
			if (ray.angle > M_PI / 2 && ray.angle < 3 * M_PI / 2)
			{
				ray.x = floor(data->pos.x / 72.0) * 72.0;
				printf(" XXXXXXXXXXXXXXX ray.x %f\n", ray.x);
				draw_point(ray.x, 72, data, BLUE);
			}
			else if ((ray.angle > 0 && ray.angle < M_PI / 2) || (ray.angle > 3 * M_PI / 2 && ray.angle < 2 * M_PI))
			{
				ray.x = ceil(data->pos.x / 72.0) * 72.0;
				printf("ray.x %f\n", ray.x);
				draw_point(ray.x, 72, data, PINK);
			}
			ray.done = true;
			i--;
		}
	}
}
