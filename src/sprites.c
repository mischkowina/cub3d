#include "../cub3d.h"

void	init_sprites(t_cub *data)
{
	int		i;

	i = 0;
	data->mummy = ft_calloc(sizeof(t_data *), 4);
	if (!data->mummy)
		ft_error("Allocation of mummy struct failed.");
	while (i < 4)
	{
		data->mummy[i] = ft_calloc(sizeof(t_data), 1);
		if (!data->mummy[i])
			ft_error("Allocation of mummy struct failed.");
		i++;
	}
	data->mummy[0]->filename = ft_strdup("textures/mummy_1.xpm");
	data->mummy[1]->filename = ft_strdup("textures/mummy_2.xpm");
	data->mummy[2]->filename = ft_strdup("textures/mummy_3.xpm");
	data->mummy[3]->filename = ft_strdup("textures/mummy_4.xpm");
	i = 0;
	while (i < 4)
	{
		open_texture(data, data->mummy[i]);
		data->mummy[i++]->offset = 20;
	}
	data->chest.filename = ft_strdup("textures/chest.xpm");
	open_texture(data, &(data->chest));
	data->chest.offset = 2;
	data->tut.filename = ft_strdup("textures/tut.xpm");
	open_texture(data, &(data->tut));
	data->tut.offset = 0;
}

double	ray_sprite(t_cub *data, double tex_pos_x, double dist, t_data *sprite)
{
	int		start;
	int		end;
	double	tex_pos_y;
	int		height;
	int		col;

	start = - (HEIGHT / dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / dist) / 2 + HEIGHT / 2.0;
	height = end - start;
	if (sprite->offset > 0)
	{
		start += height / sprite->offset;
		end += height / sprite->offset;
	}
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	tex_pos_y = 0;
	while (start < end)
	{
		col = get_texture_color(tex_pos_x, tex_pos_y, sprite);
		if (col != 16777215)
			ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += 1.0 * sprite->height / (HEIGHT / dist);
		start++;
	}
	return (1.0 * sprite->width / (WIDTH / dist));
}

void	draw_sprites(t_cub *data)
{
	double	tex_pos_x;
	double	dist;
	t_data	*cur_sprite;

	data->cur_ray->x = 0;
	tex_pos_x = 0;
	data->cur_ray->dist = 2;//instead has to be determined by raycaster
	while (data->cur_ray->x < WIDTH)//ALINA: second iteration, paints sprites
	{
		//function to recalculate ray
		if (data->cur_ray->x == WIDTH / 2)//instead: identify whether it hits a sprite before any wall
		{
			dist = data->cur_ray->dist;
			cur_sprite = &(data->chest);//has to be identified too
			while (tex_pos_x < cur_sprite->width && data->cur_ray->x < WIDTH)//does not recalculate distance, so the whole sprite works with the full distance
			{
				tex_pos_x += 
					ray_sprite(data, tex_pos_x, dist, cur_sprite);
				data->cur_ray->x++;
			}
		}
		data->cur_ray->x++;
	}
}

/**
 * Increments the counter of the game and adjusts the sprite used for the
 * mummy every 10 images. Also continues the movement of the doors by 1%
 * every image.
 * @param [t_cub *] Pointer to struct storing all the input data.
*/
void	move_doors_sprites(t_cub *data)
{
	int	i;

	i = 0;
	if (data->counter < 1000)
		data->counter++;
	else
		data->counter = 0;
	if (data->counter % 10 == 0)
	{
		if (data->cur_mummy < 3)
			data->cur_mummy++;
		else
			data->cur_mummy = 0;
	}
	while (i < data->nbr_doors)
	{
		if (data->doors[i]->opening == 1 && data->doors[i]->closed > 0)
			data->doors[i]->closed--;
		if (data->doors[i]->opening == 0 && data->doors[i]->closed < 100)
			data->doors[i]->closed++;
		data->doors[i]->cur_width = 0;
		i++;
	}
}
