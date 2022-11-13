
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
 * @return [int] 0 on success, 1 on failure.
*/
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

/**
 * Function to draw a wall based on the distance to the player position, using
 * a specified texture.
 * @param dist [double] Distance to be used for calculating the wall height.
 * @param x [int] X-coordinate of the ray on the screen.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param texture [t_data *] Pointer to the struct containing all image data of
 * the texture.
 * @return [int] 0 on success, 1 on failure.
*/
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

