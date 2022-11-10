
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
	double	x;
	double	dist;
	double	chg;
	double	ray;
	t_data	*texture;

	x = 0;
	dist = 6 / cos(15) * -1;
	prep_image(data);
	texture = &(data->N_texture);
	while (x < WIDTH)
	{
		ray = dist * cos(30);
		draw_wall(ray, x, data, texture);
		if (x < (WIDTH / 2))
			chg = (6.0 / cos(45) - 6.0 / cos(15)) / (WIDTH / 2);
		else
		{
			chg = (6.0 / cos(15) - 6.0 / cos(45)) / (WIDTH / 2);
			texture = &(data->E_texture);
		}	
		dist += chg;
		x++;
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


// test function, assuming the player position is at 5,5 and looking straight into a corner at 1,1
// smallest distance is 5,27 (4/cos(15)) and biggest is the corner at 7,61 (4/cos(45)).
int	draw_wall(double dist, int x, t_cub *data, t_data *texture)
{
	int		start;
	int		end;
	double	step;
	double	tex_pos;
	int		col;

	start = - (HEIGHT / dist) / 2 + HEIGHT / 2.0;
	if (start < 0)
		start = 0;
	end = (HEIGHT / dist) / 2 + HEIGHT / 2.0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	step = 1.0 * texture->height / (HEIGHT / dist);
	tex_pos = (start - HEIGHT / 2.0 + (HEIGHT / dist) / 2.0) * step;
	while (start < end)
	{
		col = get_texture_color(x, tex_pos, texture);
		ft_mlx_pixel_put(&(data->img), x, start, col);
		tex_pos += step;
		start++;
	}
	return (0);
}

int	prep_image(t_cub *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ft_bzero(data->img.addr, WIDTH * HEIGHT * sizeof(int));
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				ft_mlx_pixel_put(&(data->img), x, y, data->col_ceiling);
			else
				ft_mlx_pixel_put(&(data->img), x, y, data->col_floor);
			x++;
		}
		y++;
	}
	return (0);
}
