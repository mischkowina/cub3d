#include "../cub3d.h"

int	allocate_doors(t_cub *data)
{
	int	i;

	i = 0;
	data->doors = ft_calloc(sizeof(t_door *), data->nbr_doors);
	while (i < data->nbr_doors)
	{	
		data->doors[i] = ft_calloc(sizeof(t_door), 1);
		data->doors[i]->closed = 100;
		data->doors[i++]->opening = 0;
	}
	return (0);
}

int	draw_door(double dist, int x, t_cub *data, t_door *door)
{
	int		start;
	int		end;
	double	step_x;
	double	step_y;
	double	tex_pos_x;
	double	tex_pos_y;
	int		door_px;

	
	tex_pos_x = 0;
	door_px = 400;//has to be handed over somehow!
	step_x = 1.0 * data->D_texture.width / door_px;
	while (tex_pos_x < data->D_texture.width)
	{
		start = - (HEIGHT / dist) / 2 + HEIGHT / 2.0;
		end = (HEIGHT / dist) / 2 + HEIGHT / 2.0;
		if (door->opening == 1)
			start += (end - start) * (100 - door->closed) / 100;
		if (start < 0)
			start = 0;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		step_y = 1.0 * data->D_texture.height / (HEIGHT / dist);
		tex_pos_y = 0;
		while (start < end)
		{
			ft_mlx_pixel_put(&(data->img), x, start, 
				get_texture_color(tex_pos_x, tex_pos_y, &(data->D_texture)));
			tex_pos_y += step_y;
			start++;
		}
		tex_pos_x += step_x;
		x++;
	}
	return (x);
}

int	open_door(t_cub *data)
{
	int	idx;
	
	//check if conditions are met: adjacent to the door and door within FOV?
	//identify idx of door
	idx = 0;//to be replaced
	data->doors[idx]->opening = 1;
	return (0);
}

int	check_door_opening(t_cub *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_doors)
	{
		if (data->doors[i]->opening == 1 && data->doors[i]->closed > 0)
			data->doors[i]->closed--;
		if (data->doors[i]->closed == 0)
			data->map[data->doors[i]->row][data->doors[i]->col] = 0;
		i++;
	}
	return (0);
}