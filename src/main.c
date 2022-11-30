
#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	data;

	check_input(argc, argv);
	init_data(&data);
	parser(argv[1], &data);
	start_game(&data);
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
void	init_data(t_cub *data)
{
	data->counter = 0;
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
	data->nbr_sprites = 0;
	data->sprite_counter = 0;
	data->sprites = NULL;
	data->cur_mummy = 0;
	data->cur_ray = ft_calloc(sizeof(t_ray), 1);
	if (!data->cur_ray)
		ft_error("Allocation of ray struct failed.");
	data->cur_ray->dist = 0.0;
	data->cur_ray->x = 0;
	data->cur_ray->nbr_objects = 0;
}

/**
 * Function to start the game. First initializes all the MLX variables.
 * Then opens the textures as images and starts the game music.
 * Lastly, creates the image to be displayed and calls the MLX loop and 
 * hook functions.
 * @param [t_data *] Pointer to struct storing the input data.
*/
void	start_game(t_cub *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_error("MLX failed.");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		ft_error("MLX failed.");
	}
	open_all_textures(data);
	background_music();
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop(data->mlx_ptr);
}

/**
 * Function to render an image and put it to the screen. First, variables
 * for sprite and door movement are incremented and the image is prepped
 * with the ceiling and floor colors. Then all walls are calculated and drawn.
 * Lastly, the obstacles (doors and sprites) a ray crosses before hitting a
 * wall are drawn from furthest away to closest for every ray.
 * @param data [t_cub *] Pointer to struct storing the input data.
 * @return [int] 0 on success, 1 on failure.
*/
int	render(t_cub *data)
{
	move_doors_sprites(data);
	reset_tex_pos(data);
	prep_image(data);
	draw_walls(data);
	draw_sprites(data);//instead of calling draw_sprites and draw_doors in this order, determine how many objects the
	draw_doors(data);//ray crosses and then call the respective function once for each - from furthest to closest
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

//test function to render a door opening animation after pressing space
//to be integrated into Alina's function to handle keys
int	handle_keypress(int key, t_cub *data)
{
	if (key == KEY_SPACE)
		open_door(data);
	return (0);
}


//TO-DO: 
//sprite structs übergeben statt textures
//tex_pos_x im jeweiligen sprite/door speichern
//tex_pos_x nach jedem image wieder auf 0 setzen für alle sprites and doors