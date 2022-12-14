/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:12:08 by apielasz          #+#    #+#             */
/*   Updated: 2022/12/14 19:53:32 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Function puts a pixel of a given color into given (in t_img struct)
 * coordinates of the image.
 * @param img [t_img *] Pointer to a struct with all image data
 * @param color [int] representing the color
 */
void	pixel_put(t_img *img, int color)
{
	char	*dst;

	dst = img->addr + (img->px_y * img->line_length + \
	img->px_x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Function checks for the events and calls the right functions.
 * @param keycode Code of the key registered from keyboard
 * @param data [t_data *] Pointer to struct with all game data
 * @return int required by mlx
 */
int	key_hooks(int keycode, t_data *data)
{
	if (keycode == 53)
		close_x(data);
	else if (keycode == 13)
		w_key_pressed(data);
	else if (keycode == 0)
		a_key_pressed(data);
	else if (keycode == 1)
		s_key_pressed(data);
	else if (keycode == 2)
		d_key_pressed(data);
	else if (keycode == 123)
		rotate(data, -data->rotation_speed);
	else if (keycode == 124)
		rotate(data, data->rotation_speed);
	return (0);
}

/**
 * @brief Function closes the window, frees memory and kills the sound.
 * @param data [t_data *] Pointer to struct with all game data
 * @return int required by mlx
 */
int	close_x(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	if (data)
		free_all_shit(data);
	exit(0);
}
