/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:46:51 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 19:52:30 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Function to draw a wall based on the distance to the player position, using
 * the specified texture. Identifies the height of the wall using the distance
 * of the ray. Then, iterates through every pixel of the ray and identifies 
 * the respective color from the door texture.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param texture [t_data *] Pointer to the struct containing all image data of
 * the texture.
*/
void	ray_wall(t_data *data, t_img *texture)
{
	int		start;
	int		end;
	double	step;
	double	tex_pos_y;
	int		col;

	start = - (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	step = 1.0 * texture->height / (HEIGHT / data->cur_ray->full_dist);
	tex_pos_y = (start - HEIGHT / 2.0
			+ (HEIGHT / data->cur_ray->full_dist) / 2.0) * step;
	while (start < end)
	{
		col = get_texture_color(data, texture, (int)tex_pos_y);
		ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += step;
		start++;
	}
}

void	raycasting_walls(t_data *data)
{
	t_img	*texture;

	data->cur_ray->x = 0;
	data->new_time = time_now();
	while (data->cur_ray->x < WIDTH)
	{
		cast_rays(data, data->cur_ray, data->cur_ray->x);
		do_the_dda(data, data->cur_ray);
		calculate_distance(data);
		texture = identify_texture(data);
		ray_wall(data, texture);
		data->cur_ray->x++;
	}
}
