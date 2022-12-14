/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:46:51 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 17:28:23 by apielasz         ###   ########.fr       */
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

/**
 * Function to draw a ray containing a door instead of a wall. Identifies
 * the height of the wall using the distance of the ray, just as the
 * draw_wall function. Then adjusts the starting position in case the door
 * is opened to a certain degree. Lastly, iterates through every pixel
 * of the ray and identifies the respective color from the door texture.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param door [t_door *] Pointer to the struct storing the information
 * about the respective door.
*/
void	ray_door(t_data *data, t_door *door)
{
	int		start;
	int		end;
	double	tex_pos_y;
	double	step;
	int		col;

	calculate_distance(data);
	start = - (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	start += (end - start) * (100 - door->closed) / 100;
	tex_pos_y = 0;
	step = 1.0 * data->d_texture.height / (HEIGHT / data->cur_ray->full_dist);
	if (start < 0)
	{
		tex_pos_y -= start * step;
		start = 0;
	}
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start < end)
	{
		col = get_texture_color(data, &(data->d_texture), (int)tex_pos_y);
		ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start++, col);
		tex_pos_y += step;
	}
}

/**
 * Function to draw a sprite based on the distance to the player position, 
 * using the specified texture. Identifies the height of the wall using the 
 * distance of the ray. Then, shifts the position of the sprite on the 
 * y-axis by an offset, if necessary. Lastly iterates through every pixel
 * of the ray and identifies the respective color from the door texture.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param dist [double] Distance of the sprite, stays same throughout the
 * whole sprite.
 * @param sprite [t_obj *] Pointer to the struct of the sprite object.
 */
void	ray_sprite(t_data *data, t_obj *sprite)
{
	int		start;
	int		end;
	int		width;
	t_img	*texture;

	if (sprite->done == 1)
		return ;
	if (sprite->tex == NULL)
		texture = data->mummy[data->cur_mummy];
	else
		texture = sprite->tex;
	if (sprite->dist == 0.0)
		sprite->dist = get_sprite_distance(data, sprite);
	start = - (HEIGHT / sprite->dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / sprite->dist) / 2 + HEIGHT / 2.0;
	width = texture->width * (1.0 * (end - start) / texture->height);
	if (check_x_position(data, sprite, texture, width) == 0)
		return ;
	start = adjust_start(start, texture, (end - start));
	end = adjust_end(end, texture, (end - start));
	draw_sprite_ray(data, sprite, start, end);
	sprite->tex_pos_x += 1.0 * texture->width * texture->size_factor / width;
	if (sprite->tex_pos_x >= (double)texture->width)
		sprite->done = 1;
}

void	draw_sprite_ray(t_data *data, t_obj *sprite, int start, int end)
{
	int		col;
	double	tex_pos_y;
	double	step_y;
	t_img	*texture;

	if (sprite->tex == NULL)
		texture = data->mummy[data->cur_mummy];
	else
		texture = sprite->tex;
	tex_pos_y = 0;
	step_y = texture->size_factor * texture->height / (HEIGHT / sprite->dist);
	while (start < end && tex_pos_y < texture->height)
	{
		col = get_texture_color_sprite(texture,
				(int)sprite->tex_pos_x, (int)tex_pos_y);
		if (col != 16777215)
			ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += step_y;
		start++;
	}
}
