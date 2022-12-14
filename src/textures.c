/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:45:02 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 19:53:01 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Function to open a texture and receive all relevant data to work with it.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param texture [t_data *] Pointer to the struct containing all image data of
 * the texture.
*/
void	open_texture(t_data *data, t_img *texture)
{
	texture->img_ptr = mlx_xpm_file_to_image(data->mlx, texture->filename,
			&(texture->width), &(texture->height));
	if (!texture->img_ptr)
		ft_error("Failed reading .xpm file.", data);
	texture->addr = mlx_get_data_addr(texture->img_ptr, &(texture->bpp),
			&(texture->line_length), &(texture->endian));
}

/**
 * Function to open all textures and load all their relevant information.
 * @param data [t_cub *] Pointer to struct storing all the input data.
*/
void	open_all_textures(t_data *data)
{
	open_texture(data, &(data->n_texture));
	open_texture(data, &(data->e_texture));
	open_texture(data, &(data->s_texture));
	open_texture(data, &(data->w_texture));
}

/**
 * Function to identify the color at a given coordinate of a texture file. 
 * Makes sure textures get repeated on a surface by using the modulo of x and y.
 * @param x [int] X-coordinate of the specified pixel.
 * @param y [int] Y-coordinate of the specified pixel.
 * @param texture [t_data *] Pointer to the struct containing all image data of
 * the texture.
 * @return [unsigned int] The color at the specified position of the texture.
*/
int	get_texture_color(t_data *data, t_img *texture, int y)
{
	char	*dst;
	double	wall_x;
	int		tex_x;

	if (data->cur_ray->ori == 0)
		wall_x = data->pos.y + data->cur_ray->full_dist * data->cur_ray->dir.y;
	else
		wall_x = data->pos.x + data->cur_ray->full_dist * data->cur_ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (data->cur_ray->ori == 0 && data->cur_ray->dir.x > 0)
		tex_x = texture->width - tex_x - 1;
	if (data->cur_ray->ori == 1 && data->cur_ray->dir.y < 0)
		tex_x = texture->width - tex_x - 1;
	if (tex_x > texture->width)
		tex_x = tex_x % texture->width;
	if (y > texture->height)
		y = y % texture->height;
	if (y < 0)
		y = 0;
	dst = texture->addr + y * texture->line_length + tex_x * (texture->bpp / 8);
	return (*(int *)dst);
}

t_img	*identify_texture(t_data *data)
{
	t_img	*texture;

	texture = NULL;
	if (data->cur_ray->dir.y < 0 && data->cur_ray->ori == 1)
		texture = &(data->n_texture);
	else if (data->cur_ray->dir.y > 0 && data->cur_ray->ori == 1)
		texture = &(data->s_texture);
	else if (data->cur_ray->dir.x > 0 && data->cur_ray->ori == 0)
		texture = &(data->e_texture);
	else if (data->cur_ray->dir.x < 0 && data->cur_ray->ori == 0)
		texture = &(data->w_texture);
	return (texture);
}
