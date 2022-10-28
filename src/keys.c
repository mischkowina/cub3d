
#include "../cub3d.h"

void	w_key_pressed(t_data *data)
{
	data->pos_x -= data->pdx;
	data->pos_y -= data->pdy;
	handle_player(data);
}

void	s_key_pressed(t_data *data)
{
	data->pos_x += data->pdx;
	data->pos_y += data->pdy;
	handle_player(data);
}

void	a_key_pressed(t_data *data)
{
	data->p_angle -= 0.1;
	if (data->p_angle < 0)
		data->p_angle += 2 * PI;
	data->pdx = cos(data->p_angle) * 5;                                       
	data->pdy = sin(data->p_angle) * 5;
}

void	d_key_pressed(t_data *data)
{
	data->p_angle += 0.1;
	if (data->p_angle > 2 * PI)
		data->p_angle -= 2 * PI;
	data->pdx = cos(data->p_angle) * 5;
	data->pdy = sin(data->p_angle) * 5;
}