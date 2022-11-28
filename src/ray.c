
#include "../cub3d.h"

void	cast_ray(t_data *data)
{
	t_ray	ray;
	int		i;
	double	view;
	int		w;

	i = 0;
	w = (int) WIDTH / 4;
	while (i < w)
	{
		view = 2.0 * i / (double)w - 1;
		ray.dir_x = data->dir.x + data->camera_plane.x * view;
		ray.dir_y = data->dir.y + data->camera_plane.y * view;
		ray.map_x = (int) data->pos.x / 72;
		ray.map_y = (int) data->pos.y / 72;
	// this is set to avoid division by zero //
		if (ray.dir_x == 0)
		{
			// printf("ray dirx == 0\n");
			ray.delta_dist.x = INFINITY;
		}
		else
		{
			// printf("ray dirx != 0\n");
			ray.delta_dist.x = fabs(1 / ray.dir_x);
		}
		if (ray.dir_y == 0)
		{
			// printf("ray dir y == 0\n");
			ray.delta_dist.y = INFINITY;
		}
		else
		{
			// printf("ray dir y != 0\n");
			ray.delta_dist.y = fabs(1 / ray.dir_y);
		}
		calculate_step(&ray, data);
		printf("LEL %d %d\n", i, w);
		do_the_dda(&ray, data);
		i++;
	}
}

void	calculate_step(t_ray *ray, t_data *data)
{
	if (ray->dir_x < 0)
	{
		printf("ray dir x < 0\n");
		ray->step_x = -1;
		ray->side_dist.x = (data->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		printf("ray dir x > 0\n");
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - data->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir_y < 0)
	{
		printf("ray dir y < 0\n");
		ray->step_y = -1;
		ray->side_dist.y = (data->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		printf("ray dir y > 0\n");
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - data->pos.y);
	}
}

void	do_the_dda(t_ray *ray, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->ori = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->ori = 1;
		}
		// printf("mapx : %d, mapy: %d\n", ray->map_x, ray->map_y);
		if (map[ray->map_x][ray->map_y] > 0)
		{
			printf("finished\n");
			hit = 1;
			// printf("-------> finishing x: %f y:%f\n", data->pos.x + (ray->side_dist.x + ray->delta_dist.x) * ray->step_x, 
			// data->pos.y + (ray->side_dist.y + ray->delta_dist.y) * ray->step_y);
			draw_line(data->pos.x, data->pos.y, data->pos.x + (ray->side_dist.x + ray->delta_dist.x), \
			data->pos.y + (ray->side_dist.y + ray->delta_dist.y), data, PURPLE);
		}
	}
}

void	find_nearest_grid(t_ray *ray, t_data *data)
{
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
			// draw_line(data->pos.x, data->pos.y, data->pos.x - ray->hor.dx, data->pos.y - ray->hor.dy, data, PURPLE);
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
