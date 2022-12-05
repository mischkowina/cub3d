
#include "../cub3d.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void	w_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = data->pos.x + data->dir.x * MOVESPEED;
	y = data->pos.y + data->dir.y * MOVESPEED;
	if (data->map[y][x] == 0)
	{
		data->pos.x += data->dir.x * MOVESPEED;
		data->pos.y += data->dir.y * MOVESPEED;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	draw_minimap(data);
	draw_floor_and_ceiling(data);
	raycasting(data);
}

void	s_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = data->pos.x - data->dir.x * MOVESPEED;
	y = data->pos.y - data->dir.y * MOVESPEED;
	if (data->map[y][x] == 0)
	{
		data->pos.x -= data->dir.x * MOVESPEED;
		data->pos.y -= data->dir.y * MOVESPEED;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	draw_minimap(data);
	draw_floor_and_ceiling(data);
	raycasting(data);
}

void	a_key_pressed(t_data *data) //this will need camera plane vector
{
	int	x;
	int	y;

	x = data->pos.x + data->camera_plane.x * MOVESPEED;
	y = data->pos.y + data->camera_plane.y * MOVESPEED;
	if (data->map[y][x] == 0)
	{
		data->pos.x += data->camera_plane.x * MOVESPEED;
		data->pos.y += data->camera_plane.y * MOVESPEED;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	draw_minimap(data);
	draw_floor_and_ceiling(data);
	raycasting(data);
}

void	d_key_pressed(t_data *data) // this also - camera plane vector
{
	int	x;
	int	y;

	x = data->pos.x - data->camera_plane.x * MOVESPEED;
	y = data->pos.y - data->camera_plane.y * MOVESPEED;
	if (data->map[y][x] == 0)
	{
		data->pos.x -= data->camera_plane.x * MOVESPEED;
		data->pos.y -= data->camera_plane.y * MOVESPEED;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	draw_minimap(data);
	draw_floor_and_ceiling(data);
	raycasting(data);
}

void	rotate(t_data *data, double angle) //clockwise
{
	double	temp_dir_x;
	double	temp_dir_y;
	double	temp_plane_x;
	double	temp_plane_y;

	temp_dir_x = data->dir.x;
	temp_dir_y = data->dir.y;
	temp_plane_x = data->camera_plane.x;
	temp_plane_y = data->camera_plane.y;
	data->dir.x = cos(angle) * temp_dir_x - sin(angle) * temp_dir_y;
	data->dir.y = sin(angle) * temp_dir_x + cos(angle) * temp_dir_y;
	data->camera_plane.x = cos(angle) * temp_plane_x - sin(angle) * temp_plane_y;
	data->camera_plane.y = sin(angle) * temp_plane_x + cos(angle) * temp_plane_y;
	draw_minimap(data);
	draw_floor_and_ceiling(data);
	raycasting(data);
}

// OLD ROTATION // WITHOUT ROTATION MATRICES //

// void	left_key_pressed(t_data *data)
// {
// 	double	angle;
// 	t_vec	temp;

// 	angle = atan2(data->dir.y, data->dir.x);
// 	// printf("--- angle: %f\n", angle);
// 	angle -= M_PI / 36.0; // 5 degrees
// 	find_vector_values(&temp, angle);
// 	normalize_vector(&temp);
// 	// printf("--- vec.x: %f, vex.y: %f\n", temp.x, temp.y);
// 	data->dir.x = temp.x;
// 	data->dir.y = temp.y;
// 	// draw_line(data->pos.x, data->pos.y, data->dir.x + 10.0, data->dir.y + 10.0, data);
// 	// printf("--- data.dir.x: %f, data.dir.y: %f\n", data->dir.x, data->dir.y);
// }
