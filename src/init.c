
#include "../cub3d.h"

// this function is creating the window and filling it with colors
void	init(t_data *data)
{
// here I initialize the position of the player that gets later changed with WASD
	// data->pos.x = 3;
	// data->pos.y = 3;
// initialize the direction of the player's vision: N (0, 1), S (0, -1), E (1, 0), W (-1, 0)
	// data->player_dir = 'W';
	init_orientation(data);
	init_minimap(data);
	// data->dir.x = 0.0;
	// data->dir.y = 1.0;
// initialize the player angle to 2 * PI
	// data->p_angle = PI / 2;
	// data->pdx = cos(data->p_angle) * 5;
	// data->pdy = sin(data->p_angle) * 5;
	
	// data->mlx = mlx_init();
	// if (data->mlx == NULL)
	// 	return ;
	// data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	// data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// data->img.addr = mlx_get_data_addr(data->img.img_ptr, \
	// &data->img.bpp, &data->img.line_length, &data->img.endian);
	// draw_grid(data);
}

void	init_minimap(t_data *data)
{
	data->minimap.pos.x = data->pos.x * GRID_SIZE;
	data->minimap.pos.y = data->pos.y * GRID_SIZE;
}

void	init_orientation(t_data *data)
{
	if (data->player_dir == 'E')
	{
		data->dir.x = 1;
		data->dir.y = 0;
		data->camera_plane.x = 0;
		data->camera_plane.y = 0.66;
	}
	else if (data->player_dir == 'W')
	{

		data->dir.x = -1;
		data->dir.y = 0;
		data->camera_plane.x = 0;
		data->camera_plane.y = -0.66;
	}
	else if (data->player_dir == 'N')
	{
		data->dir.x = 0;
		data->dir.y = -1;
		data->camera_plane.x = 0.66;
		data->camera_plane.y = 0;
	}
	else if (data->player_dir == 'S')
	{
		data->dir.x = 0;
		data->dir.y = 1;
		data->camera_plane.x = -0.66;
		data->camera_plane.y = 0;
	}
}

/**
 * Initializes the values to be stored in the data struct, setting pointer
 * values to NULL and primitive data types to 0 or -1 (based on context).
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [int] 0 on success, 1 on failure.
*/
void	init_data(t_data *data)
{
	data->counter = 0;
	data->win = NULL;
	data->mlx = NULL;
	data->img.img_ptr = NULL;
	data->cur_weapon = 0;
	data->guns_out = 0;
	data->guns_down = 0;
	data->guns_shot = 0;
	data->cur_ray = ft_calloc(sizeof(t_ray), 1);
	if (!data->cur_ray)
		ft_error("Allocation of ray struct failed.", data);
	data->cur_ray->full_dist = 0.0;
	data->cur_ray->x = 0;
	data->cur_ray->nbr_objects = 0;
	data->mouse.x = WIDTH / 2;
	data->mouse.y = HEIGHT / 2;
	data->move_speed = 0.1;
	data->rotation_speed = 0.05;
	data->new_time = 0;
	data->old_time = 0;
	init_parsed_values(data);
	init_textures(data);
}

void	init_parsed_values(t_data *data)
{
	data->col_ceiling = -1;
	data->col_floor = -1;
	data->map = NULL;
	data->width_map = 0;
	data->height_map = 0;
	data->player_dir = '0';
	data->pos.x = -1;
	data->pos.y = -1;
	data->nbr_doors = 0;
	data->door_counter = 0;
	data->doors = NULL;
	data->nbr_sprites = 0;
	data->sprite_counter = 0;
	data->sprites = NULL;
	data->cur_mummy = 0;
}
