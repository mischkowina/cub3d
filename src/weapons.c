
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

void	ray_weapons(t_data *data, int x)
{
	int		y;
	double	tex_pos_x;
	double	tex_pos_y;
	int		col;

	tex_pos_x = (1.0 * data->weapons[data->cur_weapon]->width / WIDTH) * x;
	tex_pos_y = 0.0;
	y = 0;
	while (y < HEIGHT)
	{
		col = get_texture_color_sprite(data->weapons[data->cur_weapon], \
		(int)tex_pos_x, (int)tex_pos_y);
		// printf("x: %d, y: %d, tex_pos_x: %f, tex_pos_y %f, col: %d\n", x, y, tex_pos_x, tex_pos_y, col);
		if (col != -16777216)
			ft_mlx_pixel_put(&(data->img), x, y, col);
		tex_pos_y += 1.0 * data->weapons[data->cur_weapon]->height / HEIGHT;
		y++;
	}
}
