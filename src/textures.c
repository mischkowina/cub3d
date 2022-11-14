
#include "../cub3d.h"

/**
 * Function to open a texture and receive all relevant data to work with it.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param texture [t_data *] Pointer to the struct containing all image data of
 * the texture.
 * @return [int] 0 on success, 1 on failure.
*/
int	open_texture(t_cub *data, t_data *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx_ptr, texture->filename,
			&(texture->width), &(texture->height));
	if (!texture->img)
		ft_error("Failed reading .xpm file.");
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bpp),
			&(texture->line_length), &(texture->endian));
	return (0);
}

/**
 * Function to open all textures and load all their relevant information.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @return [int] 0 on success, 1 on failure.
*/
int	open_all_textures(t_cub *data)
{
	open_texture(data, &(data->N_texture));
	open_texture(data, &(data->E_texture));
	open_texture(data, &(data->S_texture));
	open_texture(data, &(data->W_texture));
	if (data->D_texture.filename)
		open_texture(data, &(data->D_texture));
	return (0);
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
unsigned int	get_texture_color(int x, int y, t_data *texture)
{
	char	*dst;
	int		x_new;
	int		y_new;

	x_new = x % texture->width;
	y_new = y % texture->height;
	dst = texture->addr + (y_new * texture->line_length + x_new
			* (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

// int	render_door_animation(t_cub *data, int col, int row, int idx)
// {
// 	double	x;
// 	double	ray;
// 	int		i;
// 	t_data	*texture;

// 	col = 0;
// 	row = 0;
// 	ray = 2;
// 	x = 0.0;
// 	texture = &(data->W_texture);
// 	i = WIDTH / 8;
// 	prep_image(data);
// 	idx = 0;
// 	while (x < WIDTH)
// 		draw_wall(ray, x++, data, texture);
// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		if (x == (WIDTH / 2 - i))
// 			x = draw_door(ray, x, data);
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	return (0);
// }
