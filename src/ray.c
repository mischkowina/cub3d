
#include "../cub3d.h"

void	cast_ray(t_data *data)
{
	t_ray	ray;
	int		i;

	ray.done = false;
	// ray.ver_grid = data->pos.x;
	// ray.hor_grid = data->pos.y;
	i = 1;
	while (ray.done == false)
	{
		while (i > 0)
		{
			find_nearest_grid(&ray, data);
			calculate_small_ray(&ray, data);
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
		ray->hor_grid = floor(data->pos.y / 72.0) * 72.0;
		// printf("ray->hor_grid: %f\n", ray->hor_grid);
		draw_point(72, ray->hor_grid, data, RED);
	}
		else if (ray->angle > M_PI) // the ray is looking down
	{
		ray->hor_grid = ceil(data->pos.y / 72.0) * 72.0;
		// printf("ray->hor_grid: %f\n", ray->hor_grid);
		draw_point(72, ray->hor_grid, data, GREEN);
		}

		// |||| check vertical lines |||| //
	if (ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2) // the ray is looking left
	{
		ray->ver_grid = floor(data->pos.x / 72.0) * 72.0;
		// printf("ray->ver_grid %f\n", ray->ver_grid);
		draw_point(ray->ver_grid, 72, data, BLUE);
	}
	else if ((ray->angle > 0 && ray->angle < M_PI_2) || (ray->angle > 3 * M_PI_2 && ray->angle < 2 * M_PI)) // ray is looking right
	{
		ray->ver_grid = ceil(data->pos.x / 72.0) * 72.0;
		// printf("ray->ver_grid %f\n", ray->ver_grid);
		draw_point(ray->ver_grid, 72, data, PINK);
	}
}

void	calculate_small_ray(t_ray *ray, t_data *data)
{
	double	alpha;

	alpha = 0;
	// calculate the alpha that will be used in future calculations //
	if (ray->angle > 0 && ray->angle < M_PI_2)
		alpha = M_PI_2 - ray->angle;
	else if (ray->angle > M_PI_2 && ray->angle < M_PI)
		alpha = ray->angle - M_PI_2;
	else if (ray->angle > M_PI && ray->angle < 3 * M_PI_2)
	{
		alpha = 1.5 * M_PI - ray->angle;
		printf("------> alpha: %f\n", alpha * 180 / M_PI);
	}
	else if (ray->angle > 3 * M_PI_2 && ray->angle < 2 * M_PI)
		alpha = ray->angle - 3 * M_PI_2;
	else if (ray->angle == 0 || ray->angle == M_PI_2 || ray->angle == M_PI || ray->angle == 3 * M_PI_2 || ray->angle == 2 * M_PI)
		alpha = 0;
	// calculate dy and dx for horizontal gridlines //
	ray->hor.dy = fabs(data->pos.y - ray->hor_grid);
	ray->hor.dx = tan(alpha) * ray->hor.dy;
	// calculate dy and dx for vertical gridlines //
	ray->ver.dx = fabs(data->pos.x - ray->ver_grid);
	ray->ver.dy = ray->ver.dx / tan(alpha);
	// calculate the small ray, aka the hypotenuse for both horizontal and vertical //
	ray->hor.small_ray = sqrt((ray->hor.dy * ray->hor.dy) + (ray->hor.dx * ray->hor.dx));
	ray->ver.small_ray = sqrt((ray->ver.dy * ray->ver.dy) + (ray->ver.dx * ray->ver.dx));
	// to visualise small ray //
	// if (ray->angle > 0 && ray->angle < M_PI_2)
	// {
	// 	if (ray->hor.small_ray < ray->ver.small_ray)
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x + ray->hor.dx, data->pos.y - ray->hor.dy, data, PURPLE);
	// 	else
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x + ray->ver.dx, data->pos.y - ray->ver.dy, data, PURPLE);
	// }
	// else if (ray->angle > M_PI_2 && ray->angle < M_PI)
	// {
	// 	if (ray->hor.small_ray < ray->ver.small_ray)
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x - ray->hor.dx, data->pos.y - ray->hor.dy, data, PURPLE);
	// 	else
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x - ray->ver.dx, data->pos.y - ray->ver.dy, data, PURPLE);
	// }
	// else if (ray->angle > M_PI && ray->angle < 3 * M_PI_2)
	// {
	// 	if (ray->hor.small_ray < ray->ver.small_ray)
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x - ray->hor.dx, data->pos.y + ray->hor.dy, data, PURPLE);
	// 	else
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x - ray->ver.dx, data->pos.y + ray->ver.dy, data, PURPLE);
	// }
	// else if (ray->angle > 3 * M_PI_2 && ray->angle < 2 * M_PI)
	// {
	// 	if (ray->hor.small_ray < ray->ver.small_ray)
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x + ray->hor.dx, data->pos.y + ray->hor.dy, data, PURPLE);
	// 	else
	// 		draw_line(data->pos.x, data->pos.y, data->pos.x + ray->ver.dx, data->pos.y + ray->ver.dy, data, PURPLE);
	// }
	
}
