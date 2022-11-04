
#include "../cub3d.h"

void	w_key_pressed(t_data *data)
{
	data->pos.x -= data->dir.x;
	data->pos.y -= data->dir.y;
	handle_player(data);
}

void	s_key_pressed(t_data *data)
{
	data->pos.x += data->dir.x;
	data->pos.y += data->dir.y;
	handle_player(data);
}

void	a_key_pressed(t_data *data)
{
	data->pos.x += data->dir.x;
	data->pos.y += data->dir.y;
	handle_player(data);
}

void	d_key_pressed(t_data *data)
{
	data->pos.x -= data->dir.x;
	data->pos.y -= data->dir.y;
	handle_player(data);
}

void	right_key_pressed(t_data *data)
{
	double	angle;
	t_vec	temp;

	angle = atan2(data->dir.y, data->dir.x);
	angle += M_PI / 36; // 5 degrees
	find_vector_values(&temp, angle);
	normalize_vector(&temp);
	data->dir.x = temp.x;
	data->dir.y = temp.y;
}

void	left_key_pressed(t_data *data)
{
	double	angle;
	t_vec	temp;

	angle = atan2(data->dir.y, data->dir.x);
	angle -= M_PI / 36; // 5 degrees
	find_vector_values(&temp, angle);
	normalize_vector(&temp);
	data->dir.x = temp.x;
	data->dir.y = temp.y;
}
