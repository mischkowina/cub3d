
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

/**
 * Function to draw a wall based on the distance to the player position, using
 * the specified texture. Identifies the height of the wall using the distance
 * of the ray. Then, iterates through every pixel of the ray and identifies 
 * the respective color from the door texture.
 * @param dist [double] Distance to be used for calculating the wall height.
 * @param x [int] X-coordinate of the ray on the screen.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param texture [t_data *] Pointer to the struct containing all image data of
 * the texture.
*/
void	ray_wall(t_cub *data, t_data *texture)
{
	int		start;
	int		end;
	double	step;
	double	tex_pos;
	int		col;

	start = - (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	step = 1.0 * texture->height / (HEIGHT / data->cur_ray->dist);
	tex_pos = (start - HEIGHT / 2.0
			+ (HEIGHT / data->cur_ray->dist) / 2.0) * step;
	while (start < end)
	{
		col = get_texture_color(data->cur_ray->x, tex_pos, texture);
		ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos += step;
		start++;
	}
}

void	draw_walls(t_cub *data)
{
	t_data	*texture;

	data->cur_ray->dist = 2;//instead has to be determined by raycaster
	data->cur_ray->x = 0;
	texture = &(data->E_texture);//instead, determine which texture has to be chosen based on the direction of the wall
	while (data->cur_ray->x < WIDTH)//ALINA: first iteration: always give distance to the next wall, ignore doors
	{
		//function to calculate the distance to the wall and save it in ray struct, also return how wide a door is if it hits it and save it in door struct (cur_width)
		ray_wall(data, texture);
		data->cur_ray->x++;
	}
}