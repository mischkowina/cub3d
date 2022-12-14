/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:05:46 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 09:25:04 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cast_rays(t_data *data, t_ray *ray, int i)
{
	double	view;

	view = 2 * i / (double) WIDTH - 1;
	ray->dir.x = data->dir.x + data->camera_plane.x * view;
	ray->dir.y = data->dir.y + data->camera_plane.y * view;
	ray->map_x = (int) data->pos.x;
	ray->map_y = (int) data->pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
	calculate_step(data, ray);
}

void	do_the_dda(t_data *data, t_ray *ray)
{
	int	hit;
	int	i;

	hit = 0;
	i = 0;
	while (hit == 0)
	{
		dda_math(ray);
		if (data->map[ray->map_y][ray->map_x] == 1)
			hit = 1;
		if (data->map[ray->map_y][ray->map_x] > 3)
		{
			while (i < data->nbr_sprites)
			{
				if (data->sprites[i]->col == ray->map_x
					&& data->sprites[i]->row == ray->map_y)
				{
					if (data->sprites[i]->nbr_rays == 0)
						data->sprites[i]->first_ray = data->cur_ray->x;
					data->sprites[i]->nbr_rays++;
				}
				i++;
			}
		}
	}
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

void	dda_math(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x * 1.0;
		ray->ori = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y * 1.0;
		ray->ori = 1;
	}
}

void	calculate_step(t_data *data, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (data->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - data->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (data->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - data->pos.y) * ray->delta_dist.y;
	}
}

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

void	raycasting(t_data *data)
{
	int		i;

	raycasting_walls(data);
	data->cur_ray->x = 0;
	while (data->cur_ray->x < WIDTH)
	{
		cast_rays(data, data->cur_ray, data->cur_ray->x);
		do_the_dda_sprites(data, data->cur_ray);
		while (data->cur_ray->nbr_objects > 0)
		{
			cast_rays(data, data->cur_ray, data->cur_ray->x);
			i = identify_object(data, data->cur_ray);
			if (i == 3)
				ray_door(data, (t_door *)data->cur_ray->cur_obj);
			else if (i == 4)
				ray_sprite(data, (t_obj *)data->cur_ray->cur_obj);
			else
				ft_error("Problem to identify object.", data);
			data->cur_ray->nbr_objects--;
		}
		if (data->guns_out == 1)
			ray_weapons(data, data->cur_ray->x);
		data->cur_ray->x++;
	}
	update_move_rot_speeds(data);
}
