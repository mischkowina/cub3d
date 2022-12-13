#include "../cub3d.h"

int	parse_sprites(char c, int row, int col, t_data *data)
{
	if (c == 'M')
		data->map[row][col] = 4;
	else if (c == 'T')
		data->map[row][col] = 5;
	else if (c == 'C')
		data->map[row][col] = 6;
	else
		return (1);
	data->nbr_sprites++;
	return (0);
}

void	fill_sprite(t_data *data, int row, int col)
{
	data->sprites[data->sprite_counter]->col = col;
	data->sprites[data->sprite_counter]->row = row;
	data->sprites[data->sprite_counter]->tex_pos_x = 0.0;
	data->sprites[data->sprite_counter]->done = 0;
	if (data->map[row][col] == 4)
		data->sprites[data->sprite_counter++]->tex = NULL;
	else if (data->map[row][col] == 5)
		data->sprites[data->sprite_counter++]->tex = &(data->tut);
	else if (data->map[row][col] == 6)
		data->sprites[data->sprite_counter++]->tex = &(data->chest);
}

void	init_sprites(t_data *data)
{
	int		i;

	i = 0;
	data->mummy = ft_calloc(sizeof(t_img *), 4);
	if (!data->mummy)
		ft_error(NULL, data);
	while (i < 4)
	{
		data->mummy[i] = ft_calloc(sizeof(t_img), 1);
		if (!data->mummy[i])
			ft_error(NULL, data);
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
		data->mummy[i]->offset = 20;
		data->mummy[i++]->size_factor = 1.0;
	}
	data->chest.filename = ft_strdup("textures/chest.xpm");
	open_texture(data, &(data->chest));
	data->chest.offset = 1.4;
	data->chest.size_factor = 3.0;
	data->tut.filename = ft_strdup("textures/tut.xpm");
	open_texture(data, &(data->tut));
	data->tut.offset = 20;
	data->tut.size_factor = 1.0;
}

void	*check_if_sprite(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	data->cur_ray->cur_obj = NULL;
	while (i < data->nbr_sprites)
	{
		if (data->sprites[i]->col == x && data->sprites[i]->row == y)
			data->cur_ray->cur_obj = (void *)data->sprites[i];
		i++;
	}
	return (data->cur_ray->cur_obj);
}

double	get_sprite_distance(t_data *data, t_obj	*sprite)
{
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
	double	dist;

	x = 1.0 * sprite->col + 0.5;
	y = 1.0 * sprite->row + 0.5;
	if (x > data->pos.x)
		delta_x = x - data->pos.x;
	else
		delta_x = data->pos.x - x;
	if (y > data->pos.y)
		delta_y = y - data->pos.y;
	else
		delta_y = data->pos.y - y;
	dist = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	return (dist);
}

void	move_reset_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_sprites)
	{
		data->sprites[i]->tex_pos_x = 0;
		data->sprites[i]->dist = 0.0;
		data->sprites[i]->width = 0;
		data->sprites[i]->nbr_rays = 0;
		data->sprites[i++]->done = 0;
	}
	if (data->counter % 10 == 0)
	{
		if (data->cur_mummy < 3)
			data->cur_mummy++;
		else
			data->cur_mummy = 0;
	}
}
