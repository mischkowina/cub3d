/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:41:45 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 11:31:45 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_sprites(t_data *data)
{
	init_mummies(data);
	data->chest.filename = ft_strdup("textures/chest.xpm");
	open_texture(data, &(data->chest));
	data->chest.offset = 1.4;
	data->chest.size_factor = 3.0;
	data->tut.filename = ft_strdup("textures/tut.xpm");
	open_texture(data, &(data->tut));
	data->tut.offset = 20;
	data->tut.size_factor = 1.2;
}

void	init_mummies(t_data *data)
{
	int		i;

	i = 0;
	data->mummy = ft_calloc(sizeof(t_img *), 4);
	if (!data->mummy)
		ft_error(NULL, data);
	while (i < 4)
	{
		data->mummy[i] = ft_calloc(sizeof(t_img), 1);
		if (!data->mummy[i])
			ft_error(NULL, data);
		i++;
	}
	data->mummy[0]->filename = ft_strdup("textures/mummy_1.xpm");
	data->mummy[1]->filename = ft_strdup("textures/mummy_2.xpm");
	data->mummy[2]->filename = ft_strdup("textures/mummy_3.xpm");
	data->mummy[3]->filename = ft_strdup("textures/mummy_4.xpm");
	i = 0;
	while (i < 4)
	{
		open_texture(data, data->mummy[i]);
		data->mummy[i]->offset = 20;
		data->mummy[i++]->size_factor = 1.0;
	}
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
