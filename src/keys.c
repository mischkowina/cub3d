
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
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
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
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
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
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
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
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
}