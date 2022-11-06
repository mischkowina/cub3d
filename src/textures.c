
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

	x = 200;
	y = 400;
	
	ft_bzero(data->img.addr, WIDTH * HEIGHT * sizeof(int));
	//INITIALIZE/LOAD TEXTURES WITH THIS function
	data->img.img = mlx_xpm_file_to_image(data->mlx_ptr, data->N_texture.filename, &x, &y);
	//OPEN: WHAT DO X & Y DO?????
	// x = 0;
	// y = 0;
	// while (y < HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		if (y < (HEIGHT / 2) && x < (WIDTH / 2))
	// 			//ft_mlx_pixel_put(img, x, y, col);
	// 		else if (y < (HEIGHT / 2) && x >= (WIDTH / 2))
	// 			//oben rechts
	// 		else if (y >= (HEIGHT / 2) && x < (WIDTH / 2))
	// 			//unten links
	// 		else
	// 			//unten rechts
	// 		x++;
	// 	}
	// 	y++;
	// }	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

void	ft_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
