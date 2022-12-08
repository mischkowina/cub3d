
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

	x = data->pos.x + data->dir.x * data->move_speed;
	y = data->pos.y + data->dir.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x += data->dir.x * data->move_speed;
		data->pos.y += data->dir.y * data->move_speed;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	printf("data->move_speed: %f\n", data->move_speed);
}

void	s_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = data->pos.x - data->dir.x * data->move_speed;
	y = data->pos.y - data->dir.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x -= data->dir.x * data->move_speed;
		data->pos.y -= data->dir.y * data->move_speed;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	// draw_minimap(data);
	// draw_floor_and_ceiling(data);
	// raycasting(data);
}

void	d_key_pressed(t_data *data) //this will need camera plane vector
{
	int	x;
	int	y;

	x = data->pos.x + data->camera_plane.x * data->move_speed;
	y = data->pos.y + data->camera_plane.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x += data->camera_plane.x * data->move_speed;
		data->pos.y += data->camera_plane.y * data->move_speed;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	// draw_minimap(data);
	// draw_floor_and_ceiling(data);
	// raycasting(data);
}

void	a_key_pressed(t_data *data) // this also - camera plane vector
{
	int	x;
	int	y;

	x = data->pos.x - data->camera_plane.x * data->move_speed;
	y = data->pos.y - data->camera_plane.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x -= data->camera_plane.x * data->move_speed;
		data->pos.y -= data->camera_plane.y * data->move_speed;
	}
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
	// draw_minimap(data);
	// draw_floor_and_ceiling(data);
	// raycasting(data);
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
