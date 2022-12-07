
#include "../cub3d.h"

/**
 * Function to draw a wall based on the distance to the player position, using
 * the specified texture. Identifies the height of the wall using the distance
 * of the ray. Then, iterates through every pixel of the ray and identifies 
 * the respective color from the door texture.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param texture [t_data *] Pointer to the struct containing all image data of
 * the texture.
*/
void	ray_wall(t_data *data, t_img *texture)
{
	int		start;
	int		end;
	double	step;
	double	tex_pos_y;
	int		col;

	start = - (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	step = 1.0 * texture->height / (HEIGHT / data->cur_ray->full_dist);
	tex_pos_y = (start - HEIGHT / 2.0
			+ (HEIGHT / data->cur_ray->full_dist) / 2.0) * step;
	while (start < end)
	{
		col = get_texture_color(data, texture, (int)tex_pos_y);
		ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += step;
		start++;
	}
}

/**
 * Function to draw a ray containing a door instead of a wall. Identifies
 * the height of the wall using the distance of the ray, just as the
 * draw_wall function. Then adjusts the starting position in case the door
 * is opened to a certain degree. Lastly, iterates through every pixel
 * of the ray and identifies the respective color from the door texture.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param door [t_door *] Pointer to the struct storing the information
 * about the respective door.
*/
void	ray_door(t_data *data, t_door *door)
{
	int		start;
	int		end;
	int		height;
	double	tex_pos_y;
	double	step;
	int		col;

	start = - (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->full_dist) / 2 + HEIGHT / 2.0;
	height = end - start;
	start += height * (100 - door->closed) / 100;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	step = 1.0 * data->D_texture.height / (HEIGHT / data->cur_ray->full_dist);
	tex_pos_y = (start + (height * (100 - door->closed) / 100) - HEIGHT / 2.0 
		+ (HEIGHT / data->cur_ray->full_dist) / 2.0) * step;//HERE!!
	while (start < end)
	{
		col = get_texture_color(data, &(data->D_texture), (int)tex_pos_y);
		ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += step;
		start++;
	}
}

 /**
 * Function to draw a sprite based on the distance to the player position, using
 * the specified texture. Identifies the height of the wall using the distance
 * of the ray. Then, shifts the position of the sprite on the y-axis by an
 * offset, if necessary. Lastly iterates through every pixel of the ray and 
 * identifies the respective color from the door texture.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param dist [double] Distance of the sprite, stays same throughout the
 * whole sprite.
 * @param sprite [t_obj *] Pointer to the struct of the sprite object to be drawn.
 */
void	ray_sprite(t_data *data, double dist, t_obj *sprite)
{
	int		start;
	int		end;
	double	tex_pos_y;
	int		height;
	int		col;
	t_img	*texture;//maybe move to the outside loop?

	start = - (HEIGHT / dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / dist) / 2 + HEIGHT / 2.0;
	height = end - start;
	if (sprite->tex == NULL)//see above
		texture = data->mummy[data->cur_mummy];//see above
	else//see above
		texture = sprite->tex;//see above
	if (texture->offset > 0)
	{
		start += 1.0 * height / texture->offset;
		end += 1.0 * height / texture->offset;
	}
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	tex_pos_y = 0;
	while (start < end && tex_pos_y < texture->height)
	{
		col = get_texture_color(data, texture, (int)tex_pos_y);
		if (col != 16777215)
			ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += texture->size_factor * texture->height / (HEIGHT / dist);
		start++;
	}
	sprite->tex_pos_x += (1.0 * texture->width / (WIDTH / dist) * texture->size_factor);
}


