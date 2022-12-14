/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:44:55 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 10:36:51 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	identify_object(t_data *data, t_ray *ray)
{
	int		i;

	i = 0;
	ray->cur_obj = NULL;
	while (i < ray->nbr_objects)
	{
		dda_math(ray);
		if (data->map[ray->map_y][ray->map_x] > 2)
			i++;
		else if (data->map[ray->map_y][ray->map_x] == 1)
			return (1);
	}
	if (check_if_door(data, ray->map_x, ray->map_y))
		return (3);
	if (check_if_sprite(data, ray->map_x, ray->map_y))
		return (4);
	return (1);
}

void	do_the_dda_sprites(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	ray->nbr_objects = 0;
	while (hit == 0)
	{
		dda_math(ray);
		if (data->map[ray->map_y][ray->map_x] == 1)
			hit = 1;
		if (data->map[ray->map_y][ray->map_x] > 2)
			ray->nbr_objects++;
	}
}

int	check_x_position(t_data *data, t_obj *sprite, t_img *texture, int width)
{
	int		diff;

	diff = sprite->nbr_rays - width;
	if (diff > 0)
	{
		if (data->cur_ray->x < (sprite->first_ray + (diff / 2)))
			return (0);
		else if (data->cur_ray->x >= (sprite->first_ray + width + (diff / 2)))
			return (0);
	}
	else if ((data->cur_ray->x == 0) && diff <= 0)
		sprite->tex_pos_x = -1.0 * diff
			* (texture->width * texture->size_factor / width);
	return (1);
}

int	adjust_start(int start, t_img *texture, int height)
{
	if (texture->offset > 0)
		start += 1.0 * height / texture->offset;
	if (start < 0)
		start = 0;
	return (start);
}

int	adjust_end(int end, t_img *texture, int height)
{
	if (texture->offset > 0)
		end += 1.0 * height / texture->offset;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	return (end);
}
