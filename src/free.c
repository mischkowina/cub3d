/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:41:02 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 19:53:52 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_all_shit(t_data *data)
{
	free_all_textures(data);
	if (data->map)
		free_map(data);
	if (data->cur_ray)
		free(data->cur_ray);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
}

void	free_all_textures(t_data *data)
{
	free_t_img(&(data->n_texture), data->mlx);
	free_t_img(&(data->e_texture), data->mlx);
	free_t_img(&(data->s_texture), data->mlx);
	free_t_img(&(data->w_texture), data->mlx);
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
	if (!img)
		return ;
	if (img->img_ptr)
		mlx_destroy_image(mlx_ptr, img->img_ptr);
	if (img->filename)
		free(img->filename);
}
