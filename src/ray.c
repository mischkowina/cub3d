
#include "../cub3d.h"

void	cast_ray(t_data *data)
{
	t_ray	ray;
	int		i;

	ray.done = false;
	ray.x_grid = data->pos.x;
	ray.y_grid = data->pos.y;
	i = 1;
	while (ray.done == false)
	{
		while (i > 0)
		{
			find_nearest_grid(&ray, data);
			calculate_small_ray(&ray);
			ray.done = true;
			i--;
		}
	}
}

void	find_nearest_grid(t_ray *ray, t_data *data)
{

	ray->dir_x = data->dir.x;
	ray->dir_y = data->dir.y;
	ray->angle = atan2(ray->dir_y, ray->dir_x);
	if (ray->angle < 0)
		ray->angle *= -1;
	else if (ray->angle > 0) //&& ray->angle > M_PI / 2)
		ray->angle = M_PI - ray->angle + M_PI;

	// ---- check horizontal lines ---- //
	printf(">>> this is the angle: %f, %f\n", ray->angle * 180 / M_PI, ray->angle);
	if (ray->angle < M_PI) // the ray is looking up
	{
		ray->y_grid = floor(data->pos.y / 72.0) * 72.0;
		// printf("ray->y: %f\n", ray->y_grid);
		draw_point(72, ray->y_grid, data, RED);
	}
		else if (ray->angle > M_PI) // the ray is looking down
	{
		ray->y_grid = ceil(data->pos.y / 72.0) * 72.0;
		// printf("ray->y: %f\n", ray->y_grid);
		draw_point(72, ray->y_grid, data, GREEN);
		}

		// |||| check vertical lines |||| //
	if (ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2) // the ray is looking left
	{
		ray->x_grid = floor(data->pos.x / 72.0) * 72.0;
		// printf("ray->x %f\n", ray->x_grid);
		draw_point(ray->x_grid, 72, data, BLUE);
	}
	else if ((ray->angle > 0 && ray->angle < M_PI_2) || (ray->angle > 3 * M_PI_2 && ray->angle < 2 * M_PI)) // ray is looking right
	{
		ray->x_grid = ceil(data->pos.x / 72.0) * 72.0;
		// printf("ray->x %f\n", ray->x_grid);
		draw_point(ray->x_grid, 72, data, PINK);
	}
}

void	calculate_small_ray(t_ray *ray, t_data *data)
{
	float	atan;
	
	atan = tan(ray->angle);
	// calculate for angle > 0 && < 90 //
	if (ray->angle > 0 && ray->angle < M_PI_2)
	{
		//calculate for vertical line//
		ray->ver.dy = data->pos.y - ray->y_grid;
		ray->ver.angle = M_PI_2 - ray->angle;
		atan = tan(ray->ver.angle);
		ray->ver.dx = atan * ray->ver.dy;
		ray->ver.small_ray = sqrt(ray->ver.dx * ray->ver.dx + ray->ver.dy * ray->ver.dy);

		//calculate for horizontal line//
		ray->hor.dx = ray->x_grid - data->pos.x;
		ray->hor.dy = atan * ray->hor.dx;
		ray->hor.small_ray = sqrt(ray->hor.dx * ray->hor.dx + ray->hor.dy * ray->hor.dy);
	}
}
