/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:38:49 by apielasz          #+#    #+#             */
/*   Updated: 2022/12/14 18:06:28 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Function uses rotation matrices to rotate direction and camera plane
 * vectors by a given angle. It changes the player view.
 * @param data [t_data *] Pointer to a struct with all game data
 * @param angle Double that defines angle to rotate by in radians
 */
void	rotate(t_data *data, double angle)
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
	data->camera_plane.x = cos(angle) * temp_plane_x \
	- sin(angle) * temp_plane_y;
	data->camera_plane.y = sin(angle) * temp_plane_x \
	+ cos(angle) * temp_plane_y;
}

/**
 * @brief Function rotates the player view upon mouse movement and resets mouse
 * position to the middle of the window (yes, it means you cannot escape the game
 * with your mouse while game is running hehe).
 * @param x Coordinate of mouse position in the window
 * @param y Coordinate of mouse position in the window
 * @param data [t_data *] Pointer to data struct with all game data
 * @return int required by mlx
 */
int	mouse_rotation(int x, int y, t_data *data)
{
	(void)y;
	mlx_mouse_move(data->win, data->mouse.x, data->mouse.y);
	if (x < data->mouse.x)
		rotate(data, -data->rotation_speed);
	else if (x > data->mouse.x)
		rotate(data, data->rotation_speed);
	return (0);
}

/**
 * @brief Function calculates and returns current time in miliseconds
 * @return long long current time in ms
 */
long long	time_now(void)
{
	long long		ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

/**
 * @brief Function calculates the frame per second count and updates rotation
 * and movement speeds. It ensures the rotation and movement speeds remain
 * consistent regardless of render time.
 * @param data [t_data *] Pointer to a struct with all game data
 */
void	update_move_rot_speeds(t_data *data)
{
	double	frame_time;

	data->old_time = data->new_time;
	data->new_time = time_now();
	if (data->new_time - data->old_time < 0 || \
		data->new_time - data->old_time == 0)
		frame_time = 100;
	else
		frame_time = 1000 / (data->new_time - data->old_time);
	data->move_speed = frame_time / 3500 * 5.0;
	data->rotation_speed = frame_time / 3500 * 1.5;
	data->fps = 1.0 / frame_time;
}
