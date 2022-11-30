
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

//will be replaced by one single big loop to iterate through all the rays,
//adding layer by layer (first walls, then all objects furthest to closest)
void	draw_walls(t_cub *data)
{
	t_data	*texture;

	data->cur_ray->dist = 2;//instead has to be determined by raycaster
	data->cur_ray->x = 0;
	texture = &(data->E_texture);//instead, determine which texture has to be chosen based on the direction of the wall
	while (data->cur_ray->x < WIDTH)//ALINA: first iteration: always give distance to the next wall, but count how many objects are crossed before and if they are doors, how many rays hit them
	{
		//function to calculate the distance to the wall and save it in ray struct, also return how wide a door is if it hits it and save it in door struct (cur_width)
		ray_wall(data, texture);
		data->cur_ray->x++;
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
void	ray_door(t_cub *data, t_door *door)
{
	int		start;
	int		end;
	double	tex_pos_y;
	double	step;
	int		col;

	start = - (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	start += (end - start) * (100 - door->closed) / 100;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	tex_pos_y = 0;
	step = 1.0 * data->D_texture.height / (HEIGHT / data->cur_ray->dist);
	while (start < end)
	{
		col = get_texture_color(door->tex_pos_x, tex_pos_y, &(data->D_texture));
		ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += step;
		start++;
	}
	door->tex_pos_x += 1.0 * data->D_texture.width / data->doors[0]->cur_width;
}

//will be replaced by one single big loop to iterate through all the rays,
//adding layer by layer (first walls, then all objects furthest to closest)
void	draw_doors(t_cub *data)
{
	int		i;//to be deleted
	t_door	*door;
	
	i = WIDTH / 8;//to be deleted
	data->cur_ray->x = 0;
	data->cur_ray->dist = 2;//instead has to be determined by raycaster
	door = data->doors[0];
	door->cur_width = 400;//for testing, has to be identified in first iteration
	while (data->cur_ray->x < WIDTH)//ALINA: second iteration: give distance to doors, ignore rays that hit walls
	{
		//function to recalculate ray
		if (data->cur_ray->x == (WIDTH / 2 - i))//instead: identify whether hits a door, and if yes, at which distance and which door -> maybe struct for the ray?
		{
			while (door->tex_pos_x < data->D_texture.width && data->cur_ray->x < WIDTH)
			{
				ray_door(data, door);
				data->cur_ray->x++;
				//function to recalculate ray
			}
		}
		data->cur_ray->x++;
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
void	ray_sprite(t_cub *data, double dist, t_obj *sprite)
{
	int		start;
	int		end;
	double	tex_pos_y;
	int		height;
	int		col;
	t_data	*texture;//maybe move to the outside loop?

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
		col = get_texture_color(sprite->tex_pos_x, tex_pos_y, texture);
		if (col != 16777215)
			ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += texture->size_factor * texture->height / (HEIGHT / dist);
		start++;
	}
	sprite->tex_pos_x += (1.0 * texture->width / (WIDTH / dist) * texture->size_factor);
}

//will be replaced by one single big loop to iterate through all the rays,
//adding layer by layer (first walls, then all objects furthest to closest)
void	draw_sprites(t_cub *data)
{
	double	dist;
	t_obj	*cur_sprite;
	int		width;

	data->cur_ray->x = 0;
	data->cur_ray->dist = 2;//instead has to be determined by raycaster
	while (data->cur_ray->x < WIDTH)//ALINA: second iteration, paints sprites
	{
		//function to recalculate ray
		if (data->cur_ray->x == WIDTH / 2)//instead: identify whether it hits a sprite before any wall
		{
			dist = data->cur_ray->dist;
			cur_sprite = data->sprites[0];//has to be identified too
			if (cur_sprite->tex)
				width = cur_sprite->tex->width;
			else
				width = data->mummy[data->cur_mummy]->width;
			while (cur_sprite->tex_pos_x < width && data->cur_ray->x < WIDTH)//does not recalculate distance, so the whole sprite works with the full distance
			{
				ray_sprite(data, dist, cur_sprite);//check how to handover a constant distant, maybe struct?
				data->cur_ray->x++;
			}
		}
		data->cur_ray->x++;
	}
}

