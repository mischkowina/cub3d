
#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	data;

	check_input(argc, argv);
	init_data(&data);
	parser(argv[1], &data);
	test_textures(&data);
	return (0);
}

/**
 * Checks if there is only one argument and if it is a .cub file.
 * @param argc [int] Number of command line arguments.
 * @param argv [char **] String array containing the command line arguments.
 * @return [int] 0 for valid arguments, else 1.
*/
int	check_input(int argc, char **argv)
{
	if (argc != 2)
	{
		if (argc < 2)
			ft_error(".cub file as argument required.");
		else
			ft_error("Only one argument allowed.");
	}
	if (ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 5))
		ft_error(".cub file as argument required.");
	return (0);
}

/**
 * Initializes the values to be stored in the data struct, setting pointer
 * values to NULL and primitive data types to 0 or -1 (based on context).
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [int] 0 on success, 1 on failure.
*/
int	init_data(t_cub *data)
{
	data->N_texture.filename = NULL;
	data->E_texture.filename = NULL;
	data->S_texture.filename = NULL;
	data->W_texture.filename = NULL;
	data->D_texture.filename = NULL;
	data->col_ceiling = -1;
	data->col_floor = -1;
	data->map = NULL;
	data->width_map = 0;
	data->height_map = 0;
	data->player_dir = '0';
	data->player_pos_x = -1;
	data->player_pos_y = -1;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->nbr_doors = 0;
	data->door_counter = 0;
	data->doors = NULL;
	data->cur_ray = ft_calloc(sizeof(t_ray), 1);
	return (0);
}

//Test function creating the mlx environment and rendering the texture tests
int	test_textures(t_cub *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_error("MLX failed.");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	open_all_textures(data);
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

//test function to render a simulated shifted wall
int	render(t_cub *data)
{
	int		i;
	t_data	*texture;
	double	tex_pos_x;

	tex_pos_x = 0.0;
	check_door_opening(data);
	data->cur_ray->dist = 2;
	data->cur_ray->x = 0.0;
	texture = &(data->E_texture);
	i = WIDTH / 8;
	prep_image(data);
	while (data->cur_ray->x < WIDTH)//ALINA: first iteration: always give distance to the next wall, ignore doors
	{
		draw_wall(data, texture);
		data->cur_ray->x++;
		//also identify how many rays hit each door (how wide it is) and save it in the door struct (door->cur_width)
	}
	data->cur_ray->x = 0;
	data->doors[0]->cur_width = 400;//for testing, has to be identified in first iteration
	while (data->cur_ray->x < WIDTH)//ALINA: second iteration: give distance to doors, ignore rays that hit walls
	{
		//function to recalculate ray
		if (data->cur_ray->x == (WIDTH / 2 - i))//instead: identify whether hits a door, and if yes, at which distance and which door -> maybe struct for the ray?
		{
			while (tex_pos_x < data->D_texture.width && data->cur_ray->x < WIDTH)
			{
				draw_door(data, data->doors[0], tex_pos_x);
				tex_pos_x += 1.0 * data->D_texture.width / data->doors[0]->cur_width;
				data->cur_ray->x++;
				//function to recalculate ray
			}
		}
		data->cur_ray->x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

//test function to render a door opening animation after pressing space
int	handle_keypress(int key, t_cub *data)
{
	if (key == KEY_SPACE)
		open_door(data);
	return (0);
}
