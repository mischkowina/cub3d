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
	data->nbr_doors--;
	return (0);
}

int	draw_door(double dist, int x, t_cub *data, t_door *door)
{
	int		start;
	int		end;
	double	step;
	double	tex_pos;
	int		i;

	//check if the door is opening
	//if so, only draw the percentage it is still there
	//make sure the door fills the whole tile
	door = NULL;
	i = 0;
	while (i <= data->D_texture.width)
	{
		start = - (HEIGHT / dist) / 2 + HEIGHT / 2.0;
		if (start < 0)
			start = 0;
		end = (HEIGHT / dist) / 2 + HEIGHT / 2.0;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		step = 1.0 * data->D_texture.height / (HEIGHT / dist);
		tex_pos = (start - HEIGHT / 2.0 + (HEIGHT / dist) / 2.0) * step;
		while (start < end)
		{
			ft_mlx_pixel_put(&(data->img), x, start, 
				get_texture_color(i, tex_pos, &(data->D_texture)));
			tex_pos += step;
			start++;
		}
		i++;
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
