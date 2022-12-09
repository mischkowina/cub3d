
#include "../cub3d.h"

void	init_weapons(t_data *data)
{
	int	i;

	i = 0;
	data->weapons = ft_calloc(sizeof(t_img *), 4);
	if (!data->weapons)
		ft_error(NULL, data);
	while (i < 4)
	{
		data->weapons[i] = ft_calloc(sizeof(t_img), 1);
		if (!data->weapons[i])
			ft_error(NULL, data);
		i++;
	}
	data->weapons[0]->filename = ft_strdup("textures/gun_draw.xpm");
	data->weapons[1]->filename = ft_strdup("textures/gun_up.xpm");
	data->weapons[2]->filename = ft_strdup("textures/gun_hold.xpm");
	data->weapons[3]->filename = ft_strdup("textures/gun_shot.xpm");
	i = 0;
	while (i < 4)
		open_texture(data, data->weapons[i++]);
}

void	
