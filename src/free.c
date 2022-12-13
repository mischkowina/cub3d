/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:41:02 by smischni          #+#    #+#             */
/*   Updated: 2022/12/13 21:41:04 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_all_shit(t_data *data)
{
	printf("TEST\n");
	free_all_textures(data);
	printf("TEST1\n");
	free_map(data);
	printf("TEST2\n");
	if (data->cur_ray)
		free(data->cur_ray);
	printf("TEST3\n");
	free_doors_sprites(data);
	printf("TEST4\n");
	if (data->img.addr)
		free(data->img.addr);
	printf("TEST5\n");
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx, data->img.img_ptr);
	printf("TEST6\n");
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		free(data->win);//necessary?
	}
	printf("TEST6\n");
	if (data->mlx)
		free(data->mlx);
}

void	free_all_textures(t_data *data)
{
	int	i;

	i = 0;
	free_t_img(&(data->N_texture), data->mlx);
	free_t_img(&(data->E_texture), data->mlx);
	free_t_img(&(data->S_texture), data->mlx);
	free_t_img(&(data->W_texture), data->mlx);
	free_t_img(&(data->D_texture), data->mlx);
	if (data->mummy)
	{
		while (i < 4)
		{
			if (data->mummy[i])
				free_t_img(data->mummy[i], data->mlx);
			i++;
		}
		free(data->mummy);
	}
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
	printf("TEST FREEING1\n");
	if (img->filename)
		free(img->filename);
	printf("TEST FREEING2\n");
	if (img->addr)
		free(img->addr);
	printf("TEST FREEING3\n");
	if (img->img_ptr)
		mlx_destroy_image(mlx_ptr, img->img_ptr);
	printf("TEST FREEING4\n");
	free(img->img_ptr);//necessary?
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
