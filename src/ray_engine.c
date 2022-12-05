
#include "../cub3d.h"

// this is for the solution from the guide //

void	cast_rays(t_data *data, t_ray *ray, int i)
{
	double	view;

	view = 2 * i / (double) WIDTH - 1;
	ray->dir.x = data->dir.x + data->camera_plane.x * view;
	ray->dir.y = data->dir.y + data->camera_plane.y * view;
	ray->map_x = (int) data->pos.x;
	ray->map_y = (int) data->pos.y;
	// this is set to avoid division by zero //
	if (ray->dir.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
	calculate_step(data, ray);
}

void	do_the_dda(t_data *data, t_ray *ray)
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
		if (data->map[ray->map_x][ray->map_y] > 0)
			hit = 1;
	}
}

void	calculate_step(t_data *data, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (data->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - data->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (data->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - data->pos.y) * ray->delta_dist.y;
	}
}

void	paint_my_3d_world(t_data *data, t_ray *ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int) (HEIGHT / ray->full_dist);
	draw_start = - line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	data->img.px_x = x;
	data->img.px_y = draw_start;
	while (data->img.px_y < draw_end)
	{
		pixel_put(data, PINK);
		data->img.px_y++;
	}
}

void	raycasting(t_data *data)
{
	int	i;
	t_ray	ray;

	i = WIDTH / 2;
	while (i < WIDTH)
	{
		cast_rays(data, &ray, i);
		do_the_dda(data, &ray);
		if (ray.ori == 0)
			ray.full_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			ray.full_dist = ray.side_dist.y - ray.delta_dist.y;
		// draw line //
		paint_my_3d_world(data, &ray, i);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

// this is for my solution //

// void	cast_the_rays(t_data *data)
// {
// 	t_ray	ray;
// 	int		i;
// 	double	view;
// 	int		w;

// 	i = 0;
// 	w = (int) WIDTH / 4;
// 	while (i < w)
// 	{
// 		view = 2.0 * i / (double)w - 1;
// 		ray.dir.x = data->dir.x + data->camera_plane.x * view;
// 		ray.dir.y = data->dir.y + data->camera_plane.y * view;
// 		find_nearest_grid(&ray, data);
// 		calculate_small_ray(&ray, data);
// 		i = i + 3;
// 	}
// }

// void	find_nearest_grid(t_ray *ray, t_data *data)
// {
// 	ray->angle = atan2(ray->dir.y, ray->dir.x);
// 	if (ray->angle < 0)
// 		ray->angle *= -1;
// 	else if (ray->angle > 0) //&& ray->angle > M_PI / 2)
// 		ray->angle = M_PI - ray->angle + M_PI;

// 	// ---- check horizontal lines ---- //
// 	// printf(">>> this is the angle: %f, %f\n", ray->angle * 180 / M_PI, ray->angle);
// 	if (ray->angle < M_PI) // the ray is looking up
// 	{
// 		ray->hor_grid = floor(data->pos.y / GRID_SIZE) * GRID_SIZE;
// 		// printf("ray->hor_grid: %f\n", ray->hor_grid);
// 		draw_point(GRID_SIZE, ray->hor_grid, data, RED);
// 	}
// 	else if (ray->angle > M_PI) // the ray is looking down
// 	{
// 		ray->hor_grid = ceil(data->pos.y / GRID_SIZE) * GRID_SIZE;
// 		// printf("ray->hor_grid: %f\n", ray->hor_grid);
// 		draw_point(GRID_SIZE, ray->hor_grid, data, GREEN);
// 		}

// 		// |||| check vertical lines |||| //
// 	if (ray->angle > M_PI_2 && ray->angle < ray->pi_3_2) // the ray is looking left
// 	{
// 		ray->ver_grid = floor(data->pos.x / GRID_SIZE) * GRID_SIZE;
// 		// printf("ray->ver_grid %f\n", ray->ver_grid);
// 		draw_point(ray->ver_grid, GRID_SIZE, data, BLUE);
// 	}
// 	else if ((ray->angle > 0 && ray->angle < M_PI_2) || (ray->angle > ray->pi_3_2 && ray->angle < ray->pi_2)) // ray is looking right
// 	{
// 		ray->ver_grid = ceil(data->pos.x / GRID_SIZE) * GRID_SIZE;
// 		// printf("ray->ver_grid %f\n", ray->ver_grid);
// 		draw_point(ray->ver_grid, GRID_SIZE, data, PINK);
// 	}
// }

// void	calculate_small_ray(t_ray *ray, t_data *data)
// {
// 	double	alpha;

// 	alpha = 0;
// 	// calculate the alpha that will be used in future calculations //
// 	if (ray->angle > 0 && ray->angle < M_PI_2)
// 		alpha = M_PI_2 - ray->angle;
// 	else if (ray->angle > M_PI_2 && ray->angle < M_PI)
// 		alpha = ray->angle - M_PI_2;
// 	else if (ray->angle > M_PI && ray->angle < ray->pi_3_2)
// 	{
// 		alpha = M_PI - M_PI_2 - ray->angle;
// 		// printf("------> alpha: %f\n", alpha * 180 / M_PI);
// 	}
// 	else if (ray->angle > ray->pi_3_2 && ray->angle < ray->pi_2)
// 		alpha = ray->angle - ray->pi_3_2;
// 	else if (ray->angle == 0 || ray->angle == M_PI_2 || ray->angle == M_PI || ray->angle == ray->pi_3_2 || ray->angle == ray->pi_2)
// 		alpha = 0;
// 	// calculate dy and dx for horizontal gridlines //
// 	ray->hor.dy = abs((int)data->pos.y - ray->hor_grid);
// 	ray->hor.dx = tan(alpha) * ray->hor.dy;
// 	// calculate dy and dx for vertical gridlines //
// 	ray->ver.dx = abs((int)data->pos.x - ray->ver_grid);
// 	ray->ver.dy = ray->ver.dx / tan(alpha);
// 	// calculate the small ray, aka the hypotenuse for both horizontal and vertical //
// 	ray->hor.small_ray = sqrt((ray->hor.dy * ray->hor.dy) + (ray->hor.dx * ray->hor.dx));
// 	ray->ver.small_ray = sqrt((ray->ver.dy * ray->ver.dy) + (ray->ver.dx * ray->ver.dx));

// 	// to visualise small ray //

// 	if (ray->angle > 0 && ray->angle < M_PI_2)
// 	{
// 		if (ray->hor.small_ray < ray->ver.small_ray)
// 			draw_line(data->pos.x, data->pos.y, data->pos.x + ray->hor.dx, data->pos.y - ray->hor.dy, data, PURPLE);
// 		else
// 			draw_line(data->pos.x, data->pos.y, data->pos.x + ray->ver.dx, data->pos.y - ray->ver.dy, data, PURPLE);
// 	}
// 	else if (ray->angle > M_PI_2 && ray->angle < M_PI)
// 	{
// 		if (ray->hor.small_ray < ray->ver.small_ray)
// 			draw_line(data->pos.x, data->pos.y, data->pos.x - ray->hor.dx, data->pos.y - ray->hor.dy, data, PURPLE);
// 		else
// 			draw_line(data->pos.x, data->pos.y, data->pos.x - ray->ver.dx, data->pos.y - ray->ver.dy, data, PURPLE);
// 	}
// 	else if (ray->angle > M_PI && ray->angle < ray->pi_3_2)
// 	{
// 		if (ray->hor.small_ray < ray->ver.small_ray)
// 			draw_line(data->pos.x, data->pos.y, data->pos.x - ray->hor.dx, data->pos.y + ray->hor.dy, data, PURPLE);
// 		else
// 			draw_line(data->pos.x, data->pos.y, data->pos.x - ray->ver.dx, data->pos.y + ray->ver.dy, data, PURPLE);
// 	}
// 	else if (ray->angle > ray->pi_3_2 && ray->angle < ray->pi_2)
// 	{
// 		if (ray->hor.small_ray < ray->ver.small_ray)
// 			draw_line(data->pos.x, data->pos.y, data->pos.x + ray->hor.dx, data->pos.y + ray->hor.dy, data, PURPLE);
// 		else
// 			draw_line(data->pos.x, data->pos.y, data->pos.x + ray->ver.dx, data->pos.y + ray->ver.dy, data, PURPLE);
// 	}
// }
