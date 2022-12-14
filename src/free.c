/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:41:02 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 14:12:11 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_all_shit(t_data *data)
{
	free_all_textures(data);
	free_map(data);
	if (data->cur_ray)
		free(data->cur_ray);
	free_doors_sprites(data);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		free(data->win);
	}
	if (data->mlx)
		free(data->mlx);
}

void	free_all_textures(t_data *data)
{
	free_t_img(&(data->n_texture), data->mlx);
	free_t_img(&(data->e_texture), data->mlx);
	free_t_img(&(data->s_texture), data->mlx);
	free_t_img(&(data->w_texture), data->mlx);
	free_t_img(&(data->d_texture), data->mlx);
	if (data->mummy)
		free_texture_array(data, data->mummy);
	if (data->weapons)
		free_texture_array(data, data->weapons);
	free_t_img(&(data->chest), data->mlx);
	free_t_img(&(data->tut), data->mlx);
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
}

void	free_t_img(t_img *img, void *mlx_ptr)
{
	if (img->img_ptr)
		mlx_destroy_image(mlx_ptr, img->img_ptr);
	if (img->filename)
		free(img->filename);
}

void	free_doors_sprites(t_data *data)
{
	int	i;

	i = 0;
	if (data->doors)
	{
		while (i < data->nbr_doors && data->doors[i])
			free(data->doors[i++]);
		free(data->doors);
	}
	i = 0;
	if (data->sprites)
	{
		while (i < data->nbr_sprites && data->sprites[i])
			free(data->sprites[i++]);
		free(data->sprites);
	}
}
