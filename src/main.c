
#include "../cub3d.h"

// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	check_input(argc, argv);
// 	init_data(&data);
// 	parser(argv[1], &data);
// 	start_game(&data);
// 	return (0);
// }

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
			ft_error(".cub file as argument required.", NULL);
		else
			ft_error("Only one argument allowed.", NULL);
	}
	if (ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 5))
		ft_error(".cub file as argument required.", NULL);
	return (0);
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
	data->pos.x = -1;
	data->pos.y = -1;
	data->mlx = NULL;
	data->win = NULL;
	data->nbr_doors = 0;
	data->door_counter = 0;
	data->doors = NULL;
	data->nbr_sprites = 0;
	data->sprite_counter = 0;
	data->sprites = NULL;
	data->cur_mummy = 0;
	data->cur_ray = ft_calloc(sizeof(t_ray), 1);
	if (!data->cur_ray)
		ft_error("Allocation of ray struct failed.", data);
	data->cur_ray->full_dist = 0.0;
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
void	start_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error("MLX failed.", data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		ft_error("MLX failed.", data);
	}
	open_all_textures(data);
	background_music();
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	mlx_hook(data->win, 2, (1L<<0), handle_keypress, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}

/**
 * Function to render an image and put it to the screen. First, variables
 * for sprite and door movement are incremented and the texture position for
 * is reset for all sprites. Further, the image is prepped with the ceiling 
 * and floor colors. 
 * //TBD
 * Lastly, the image is pushed to the window.
 * @param data [t_cub *] Pointer to struct storing the input data.
 * @return [int] 0 on success, 1 on failure.
*/
int	render(t_data *data)
{
	move_doors_sprites(data);
	reset_tex_pos(data);
	prep_image(data);
	draw_walls(data);//instead of calling draw walls, draw sprites and draw_doors
	draw_sprites(data);//we will need one loop to check each ray once and draw its
	draw_doors(data);//content layer by layer, from furthest to closest
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (0);
}

//test function to render a door opening animation after pressing space
//to be integrated into Alina's function to handle keys
int	handle_keypress(int key, t_data *data)
{
	if (key == KEY_SPACE)
		open_door(data);
	return (0);
}
