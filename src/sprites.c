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
	data->mummy = ft_calloc(sizeof(t_data *), 4);
	if (!data->mummy)
		ft_error("Allocation of mummy struct failed.", data);
	while (i < 4)
	{
		data->mummy[i] = ft_calloc(sizeof(t_data), 1);
		if (!data->mummy[i])
			ft_error("Allocation of mummy struct failed.", data);
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
