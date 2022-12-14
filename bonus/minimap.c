/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:24:48 by apielasz          #+#    #+#             */
/*   Updated: 2022/12/14 16:37:09 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief a function takes coordinates in which a square point is 
 * going to be drawn. The size of the point is specified by the 
 * size variable in the function.
 * @param x x coordinate of the img
 * @param y y coordinate of the img
 * @param img [t_img *] pointer to the struct with img data
 * @param color integer that specifies the color of the point
 */

void	draw_point(int x, int y, t_img *img, int color)
{
	int	size;

	size = 11;
	img->px_y = y;
	while (img->px_y < y + size)
	{
		img->px_x = x;
		while (img->px_x < x + size)
		{
			pixel_put(img, color);
			img->px_x++;
		}
		img->px_y++;
	}
}

/**
 * @brief a function draws a point in the position specified by given coordinates
 * that represent player position and draws a line that shows the direction
 * in which the player is looking.
 * @param data [t_data *] a pointer to a struct with all game data
 */

void	draw_player(t_data *data)
{
	t_vec_int	start;
	t_vec_int	end;

	start.x = data->pos.x * 11 + 15;
	start.y = data->pos.y * 11 + 15;
	end.x = data->pos.x * 11 + 15 + (data->dir.x * 20);
	end.y = data->pos.y * 11 + 15 + (data->dir.y * 20);
	draw_line(start, end, data, 0x76BAB8);
	draw_player_point(start.x, start.y, &(data->img), 0x3F7879);
}

/**
 * @brief a function that draws a point to represent player position
 * in the minimap
 * @param x x coordinate of the img
 * @param y y coordinate of the img
 * @param img [t_img *] pointer to the struct with img data
 * @param color integer that specifies the color of the point
 */

void	draw_player_point(int x, int y, t_img *img, int color)
{
	int			start_x;
	int			size;

	size = 4;
	start_x = x - size;
	img->px_y = y - size;
	while (img->px_y < y + size)
	{
		img->px_x = start_x;
		while (img->px_x < x + size)
		{
			pixel_put(img, color);
			img->px_x++;
		}
		img->px_y++;
	}
}

/**
 * @brief a function that draws a line from point specified in start to a point
 * specified in end regardless of the angle.
 * @param start [t_vec_int] struct with coordinates of starting point
 * @param end [t_vec_int] struct with coordinates if the ending point
 * @param data [t_data *] struct with all game data
 * @param color integer that specifies the color of the drawn line
 */

void	draw_line(t_vec_int start, t_vec_int end, t_data *data, int color)
{
	double	dx;
	double	dy;
	double	px_x;
	double	px_y;
	int		px;

	dx = end.x - start.x;
	dy = end.y - start.y;
	px = sqrt((dx * dx) + (dy * dy));
	dx /= px;
	dy /= px;
	px_x = start.x;
	px_y = start.y;
	while (px)
	{
		data->img.px_x = px_x;
		data->img.px_y = px_y;
		pixel_put(&(data->img), color);
		px_x += dx;
		px_y += dy;
		px--;
	}
}

/**
 * @brief function is using current data to render minimap showing door and
 * player position
 * @param data [t_data *] struct with all the data
 */

void	render_minimap(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < data->height_map)
	{
		x = 0;
		while (x < data->width_map)
		{
			if (data->map[y][x] == 1)
				color = 0xA4851A;
			else if (data->map[y][x] == 0)
				color = 0x000000;
			else if (data->map[y][x] == 3)
				color = 0x751919;
			else if (data->map[y][x] == -1)
				color = -1;
			if (color != -1)
				draw_point(x * 11 + 15, y * 11 + 15, &(data->img), color);
			x++;
		}
		y++;
	}
	draw_player(data);
}
