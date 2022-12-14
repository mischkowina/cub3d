/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:41:45 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 19:50:55 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures(t_data *data)
{
	data->n_texture.filename = NULL;
	data->n_texture.img_ptr = NULL;
	data->e_texture.filename = NULL;
	data->e_texture.img_ptr = NULL;
	data->s_texture.filename = NULL;
	data->s_texture.img_ptr = NULL;
	data->w_texture.filename = NULL;
	data->w_texture.img_ptr = NULL;
}

void	free_texture_array(t_data *data, t_img **img)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (img[i])
		{
			free_t_img(img[i], data->mlx);
			free(img[i]);
		}
		i++;
	}
	free(img);
}
