/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:33:41 by apielasz          #+#    #+#             */
/*   Updated: 2022/12/14 18:33:45 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief These functions calculate the updated player position and depending on
 * the key that was pressed direction or camera plane vectors are used.
 * Functions also check if the new positions collide with walls and implement
 * an effect of gliding against the wall.
 * @param data [t_data *] Pointer to a struct with all game data
 */
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
