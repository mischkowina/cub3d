
#include "../cub3d.h"

void	w_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = (data->pos.x + data->dir.x * 5) / 72;
	y = (data->pos.y + data->dir.y * 5) / 72;
	// printf(">>>>>> x: %d, y: %d, map[x][y]: %d\n", x, y, map[x][y]);
	if (map[x][y] == 0)
	{
		data->pos.x += data->dir.x * 5;
		data->pos.y += data->dir.y * 5;
	}
	// printf("data.dir.x: %f, data.dir.y: %f\n", data->dir.x, data->dir.y);
	// draw_line(data->pos.x, data->pos.y, data->dir.x + 10, data->dir.y + 10, data);
	handle_player(data);
}

void	s_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = (data->pos.x - data->dir.x * 5) / 72;
	y = (data->pos.y - data->dir.y * 5) / 72;
	if (map[x][y] == 0)
	{
		data->pos.x -= data->dir.x * 5;
		data->pos.y -= data->dir.y * 5;
	}
	// draw_line(data->pos.x + 10, data->pos.y + 10, data->pos.x + data->dir.x + 10, data->pos.y + data->dir.y + 10, data);
	handle_player(data);
}

void	a_key_pressed(t_data *data) //this will need camera plane vector
{
	int	x;
	int	y;

	x = (data->pos.x + data->camera_plane.x) / 72;
	y = (data->pos.y + data->camera_plane.y) / 72;
	if (map[x][y] == 0)
	{
		data->pos.x += data->camera_plane.x * 5;
		data->pos.y += data->camera_plane.y * 5;
	}
	handle_player(data);
}

void	d_key_pressed(t_data *data) // this also - camera plane vector
{
	int	x;
	int	y;

	x = (data->pos.x - data->camera_plane.x) / 72;
	y = (data->pos.y - data->camera_plane.y) / 72;
	if (map[x][y] == 0)
	{
		data->pos.x -= data->camera_plane.x * 5;
		data->pos.y -= data->camera_plane.y * 5;
	}
	handle_player(data);
}

void	right_key_pressed(t_data *data) //clockwise
{
	double	temp_dir_x;
	double	temp_dir_y;
	double	temp_plane_x;
	double	temp_plane_y;

	temp_dir_x = data->dir.x;
	temp_dir_y = data->dir.y;
	temp_plane_x = data->camera_plane.x;
	temp_plane_y = data->camera_plane.y;
	data->dir.x = cos(ROT_ANGLE) * temp_dir_x - sin(ROT_ANGLE) * temp_dir_y;
	data->dir.y = sin(ROT_ANGLE) * temp_dir_x + cos(ROT_ANGLE) * temp_dir_y;
	data->camera_plane.x = cos(ROT_ANGLE) * temp_plane_x - sin(ROT_ANGLE) * temp_plane_y;
	data->camera_plane.y = sin(ROT_ANGLE) * temp_plane_x + cos(ROT_ANGLE) * temp_plane_y;
	handle_player(data);
}

void	left_key_pressed(t_data *data) // counterclockwise
{
	double	temp_dir_x;
	double	temp_dir_y;
	double	temp_plane_x;
	double	temp_plane_y;

	temp_dir_x = data->dir.x;
	temp_dir_y = data->dir.y;
	temp_plane_x = data->camera_plane.x;
	temp_plane_y = data->camera_plane.y;
	data->dir.x = cos(ROT_ANGLE) * temp_dir_x + sin(ROT_ANGLE) * temp_dir_y;
	data->dir.y = - sin(ROT_ANGLE) * temp_dir_x + cos(ROT_ANGLE) * temp_dir_y;
	data->camera_plane.x = cos(ROT_ANGLE) * temp_plane_x + sin(ROT_ANGLE) * temp_plane_y;
	data->camera_plane.y = - sin(ROT_ANGLE) * temp_plane_x + cos(ROT_ANGLE) * temp_plane_y;
	handle_player(data);
}

// OLD ROTATION // WITHOUT ROTATION MATRICES

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
