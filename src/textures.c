
#include "../cub3d.h"

int	test_textures(t_cub *data)//TEST; DELETE LATER
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_error("MLX failed.");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	open_all_textures(data);
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	render(t_cub *data)
{
	int	x;
	int	y;
	int	col;

	x = 0;
	y = 0;
	ft_bzero(data->img.addr, WIDTH * HEIGHT * sizeof(int));
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < (HEIGHT / 3))
				col = (int)get_texture_color(x, y, &(data->N_texture));
			else if (y >= (HEIGHT / 3 * 2))
				col = (int)get_texture_color(x, (y - (HEIGHT / 3 * 2)), &(data->E_texture));
			else
				col = (int)get_texture_color(x, (y - (HEIGHT / 3)), &(data->S_texture));
			ft_mlx_pixel_put(&(data->img), x, y, col);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

void	ft_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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

int	open_all_textures(t_cub *data)
{
	open_texture(data, &(data->N_texture));
	open_texture(data, &(data->E_texture));
	open_texture(data, &(data->S_texture));
	open_texture(data, &(data->W_texture));
	//ADD DOOR TEXTURES FOR BONUS
	return (0);
}

//get the color at a certain position of an image
unsigned int	get_texture_color(int x, int y, t_data *texture)
{
	char	*dst;
	int		x_new;
	int		y_new;

	x_new = x % texture->width;
	y_new = y % texture->height;
	dst = texture->addr + (y_new * texture->line_length + x_new * (texture->bpp/8));
	return (*(unsigned int *)dst);
}