
#include "../cub3d.h"

/**
 * Function to color a specified pixel of the image in the specified color.
 * @param img [t_data *] Pointer to the image data.
 * @param x [int] X-coordinate of the pixel to be colored.
 * @param y [int] Y-coordinate of the pixel to be colored.
 * @param color [int] Integer representation of the color.
*/
void	ft_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * Prepares the image to be displayed on the screen by first clearing the memory
 * and then adding ceiling and floor colors. The pixels for the walls are added
 * at a later point.
 * @param data [t_cub *] Pointer to struct storing all the input data.
*/
void	prep_image(t_cub *data)
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
}
