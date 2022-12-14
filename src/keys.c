
#include "../cub3d.h"

void	w_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = data->pos.x;
	y = data->pos.y + data->dir.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.y += data->dir.y * data->move_speed;
	}
	x = data->pos.x + data->dir.x * data->move_speed;
	y = data->pos.y;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x += data->dir.x * data->move_speed;
	}
}

void	s_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = data->pos.x;
	y = data->pos.y - data->dir.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.y -= data->dir.y * data->move_speed;
	}
	x = data->pos.x - data->dir.x * data->move_speed;
	y = data->pos.y;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x -= data->dir.x * data->move_speed;
	}
}

void	d_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = data->pos.x;
	y = data->pos.y + data->camera_plane.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.y += data->camera_plane.y * data->move_speed;
	}
	x = data->pos.x + data->camera_plane.x * data->move_speed;
	y = data->pos.y;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x += data->camera_plane.x * data->move_speed;
	}
}

void	a_key_pressed(t_data *data)
{
	int	x;
	int	y;

	x = data->pos.x;
	y = data->pos.y - data->camera_plane.y * data->move_speed;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.y -= data->camera_plane.y * data->move_speed;
	}
	x = data->pos.x - data->camera_plane.x * data->move_speed;
	y = data->pos.y;
	if (check_if_accessible(data, x, y) == 1)
	{
		data->pos.x -= data->camera_plane.x * data->move_speed;
	}
}