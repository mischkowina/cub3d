
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
	open_texture(data, &(data->N_texture));
	open_texture(data, &(data->E_texture));
	open_texture(data, &(data->S_texture));
	open_texture(data, &(data->W_texture));
	if (data->D_texture.filename)
		open_texture(data, &(data->D_texture));
	init_sprites(data);
	init_weapons(data);
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
	dst = texture->addr + (y * texture->line_length + tex_x * (texture->bpp / 8));
	return (*(int *)dst);
}

int	get_texture_color_sprite(t_img *texture, int x, int y)
{
	char	*dst;
	int		tex_pos_x;
	int		tex_pos_y;

	tex_pos_x = x % texture->width;
	tex_pos_y = y % texture->height;
	dst = texture->addr + (tex_pos_y * texture->line_length + \
	tex_pos_x * (texture->bpp / 8));
	return (*(int *)dst);
}

t_img	*identify_texture(t_data *data)
{
	t_img	*texture;
	
	texture = NULL;//can it happen that none of these apply?
	if (data->cur_ray->dir.y < 0 && data->cur_ray->ori == 1) // N
		texture = &(data->N_texture);
	else if (data->cur_ray->dir.y > 0 && data->cur_ray->ori == 1) // S
		texture = &(data->S_texture);
	else if (data->cur_ray->dir.x > 0 && data->cur_ray->ori == 0) // E
		texture = &(data->E_texture);
	else if (data->cur_ray->dir.x < 0 && data->cur_ray->ori == 0) // W
		texture = &(data->W_texture);
	return (texture);
}
