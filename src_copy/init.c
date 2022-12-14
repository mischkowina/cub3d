/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:49:16 by apielasz          #+#    #+#             */
/*   Updated: 2022/12/14 18:51:12 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Function reads the player position and initializes the values
 * of the direction vector as well as camera plane vector
 * @param data [t_data *] Pointer to a struct with all game data
 */
void	init_orientation(t_data *data)
{
	if (data->player_dir == 'E')
	{
		data->dir.x = 1;
		data->dir.y = 0;
		data->camera_plane.x = 0;
		data->camera_plane.y = 0.66;
	}
	else if (data->player_dir == 'W')
	{
		data->dir.x = -1;
		data->dir.y = 0;
		data->camera_plane.x = 0;
		data->camera_plane.y = -0.66;
	}
	init_orientation_more(data);
}

/**
 * @brief This function exists purely bc norminette was bitching.
 * It's a continuation of the the init_orientation function
 * @param data [t_data *] Pointer to a struct with all game data
 */
void	init_orientation_more(t_data *data)
{
	if (data->player_dir == 'N')
	{
		data->dir.x = 0;
		data->dir.y = -1;
		data->camera_plane.x = 0.66;
		data->camera_plane.y = 0;
	}
	else if (data->player_dir == 'S')
	{
		data->dir.x = 0;
		data->dir.y = 1;
		data->camera_plane.x = -0.66;
		data->camera_plane.y = 0;
	}
}

/**
 * Initializes the values to be stored in the data struct, setting pointer
 * values to NULL and primitive data types to 0 or -1 (based on context).
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [int] 0 on success, 1 on failure.
*/
void	init_data(t_data *data)
{
	// data->counter = 0;
	data->win = NULL;
	data->mlx = NULL;
	data->img.img_ptr = NULL;
	// data->cur_weapon = 0;
	// data->guns_out = 0;
	// data->guns_down = 0;
	// data->guns_shot = 0;
	data->cur_ray = ft_calloc(sizeof(t_ray), 1);
	if (!data->cur_ray)
		ft_error("Allocation of ray struct failed.", data);
	data->cur_ray->full_dist = 0.0;
	data->cur_ray->x = 0;
	data->cur_ray->nbr_objects = 0;
	data->mouse.x = WIDTH / 2;
	data->mouse.y = HEIGHT / 2;
	data->move_speed = 0.1;
	data->rotation_speed = 0.05;
	data->new_time = 0;
	data->old_time = 0;
	init_parsed_values(data);
	init_textures(data);
}

void	init_parsed_values(t_data *data)
{
	data->col_ceiling = -1;
	data->col_floor = -1;
	data->map = NULL;
	data->width_map = 0;
	data->height_map = 0;
	data->player_dir = '0';
	data->pos.x = -1;
	data->pos.y = -1;
	// data->nbr_doors = 0;
	// data->door_counter = 0;
	// data->doors = NULL;
	// data->nbr_sprites = 0;
	// data->sprite_counter = 0;
	// data->sprites = NULL;
	// data->cur_mummy = 0;
}
