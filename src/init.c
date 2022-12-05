
#include "../cub3d.h"

// this function is creating the window and filling it with colors
void	init(t_data *data)
{
// here I initialize the position of the player that gets later changed with WASD
	data->pos.x = 3;
	data->pos.y = 3;
// initialize the direction of the player's vision: N (0, 1), S (0, -1), E (1, 0), W (-1, 0)
	data->player_dir = 'W';
	init_orientation(data);
	init_minimap(data);
	// data->dir.x = 0.0;
	// data->dir.y = 1.0;
// initialize the player angle to 2 * PI
	// data->p_angle = PI / 2;
	// data->pdx = cos(data->p_angle) * 5;
	// data->pdy = sin(data->p_angle) * 5;
	
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return ;
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, \
	&data->img.bpp, &data->img.line_length, &data->img.endian);
	draw_grid(data);
}

void	init_minimap(t_data *data)
{
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
}

void	init_orientation(t_data *data)
{
	if (data->player_dir == 'S')
	{
		data->dir.x = 1;
		data->dir.y = 0;
		data->camera_plane.x = 0;
		data->camera_plane.y = -0.66;
	}
	else if (data->player_dir == 'N')
	{
		data->dir.x = -1;
		data->dir.y = 0;
		data->camera_plane.x = 0;
		data->camera_plane.y = 0.66;
	}
	else if (data->player_dir == 'W')
	{
		data->dir.x = 0;
		data->dir.y = -1;
		data->camera_plane.x = -0.66;
		data->camera_plane.y = 0;
	}
	else if (data->player_dir == 'E')
	{
		data->dir.x = 0;
		data->dir.y = 1;
		data->camera_plane.x = 0.66;
		data->camera_plane.y = 0;
	}
}
