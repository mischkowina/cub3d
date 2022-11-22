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
		open_texture(data, data->mummy[i++]);
}

double	draw_sprites(t_cub *data, double tex_pos_x)
{
	int		start;
	int		end;
	double	tex_pos_y;
	int		height;
	int		col;

	start = - (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	height = end - start;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	tex_pos_y = 0;
	while (start < end)
	{
		col = get_texture_color(tex_pos_x, tex_pos_y, data->mummy[data->cur_mummy]);
		if (col != 16777215)
			ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += 1.0 * data->mummy[data->cur_mummy]->height / (HEIGHT / data->cur_ray->dist);
		start++;
	}
	return (1.0 * data->mummy[data->cur_mummy]->width / (WIDTH / data->cur_ray->dist));
}
