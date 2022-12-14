/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:38:49 by apielasz          #+#    #+#             */
/*   Updated: 2022/12/14 19:52:50 by smischni         ###   ########.fr       */
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
