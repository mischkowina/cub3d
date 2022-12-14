/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:40:44 by smischni          #+#    #+#             */
/*   Updated: 2022/12/13 21:40:47 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Function to allocate and initialize a struct for every door, 
 * holding a flag if the door is opening or not, the precentage
 * to which it is closed and the width of the door in pixels
 * for the current image.
 * @param data [t_data *] Pointer to struct storing the input data.
*/
void	allocate_doors_sprites(t_data *data)
{
	int	i;

	i = 0;
	data->doors = ft_calloc(sizeof(t_door *), data->nbr_doors);
	if (!data->doors)
		ft_error(NULL, data);
	while (i < data->nbr_doors)
	{	
		data->doors[i] = ft_calloc(sizeof(t_door), 1);
		if (!data->doors[i])
			ft_error(NULL, data);
		data->doors[i]->closed = 100;
		data->doors[i++]->opening = 0;
	}
	i = 0;
	data->sprites = ft_calloc(sizeof(t_obj *), data->nbr_sprites);
	if (!data->sprites)
		ft_error(NULL, data);
	while (i < data->nbr_sprites)
	{	
		data->sprites[i] = ft_calloc(sizeof(t_obj), 1);
		if (!data->sprites[i])
			ft_error(NULL, data);
		data->sprites[i++]->tex = NULL;
	}
}

/**
 * Increments the counter of the game and adjusts the sprite used for the
 * mummy every 10 images. Also continues the movement of the doors by 1%
 * every image.
 * @param [t_cub *] Pointer to struct storing all the input data.
*/
void	move_doors_sprites(t_data *data)
{
	int	i;

	i = 0;
	if (data->counter < 1000)
		data->counter++;
	else
		data->counter = 0;
	while (i < data->nbr_doors)
	{
		if (data->doors[i]->opening == 1 && data->doors[i]->closed > 0)
			data->doors[i]->closed -= 2;
		if (data->doors[i]->opening == 0 && data->doors[i]->closed < 100)
			data->doors[i]->closed += 2;
		i++;
	}
	move_reset_sprites(data);
	if (data->counter % 2 == 0)
	{
		move_weapons(data);
	}
}

/**
 * Function to interact with a door. First checks if there is a door in the
 * proximity / FOV (???) to interact with. If so, changes the opening flag of
 * the door, depending on whether it was currently closing or opening.
 * @param [t_cub *] Pointer to struct storing all the input data.
*/
void	open_door(t_data *data)
{
	t_door	*door;

	door = check_door_ahead(data);
	if (!door)
		return ;
	if (door->opening == 0)
		door->opening = 1;
	else
		door->opening = 0;
	play_sound("sounds/door.wav");
}

void	*check_if_door(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	data->cur_ray->cur_obj = NULL;
	while (i < data->nbr_doors)
	{
		if (data->doors[i]->col == x && data->doors[i]->row == y)
			data->cur_ray->cur_obj = (void *)data->doors[i];
		i++;
	}
	return (data->cur_ray->cur_obj);
}
