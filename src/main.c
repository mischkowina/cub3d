
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
 * Initializes the values to be stored in the data struct, setting string
 * values to NULL and the color values to an impossible value.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [int] 0 on success, 1 on failure.
*/
int	init_data(t_cub *data)
{
	data->N_texture.filename = NULL;
	data->E_texture.filename = NULL;
	data->S_texture.filename = NULL;
	data->W_texture.filename = NULL;
	data->col_ceiling = 33554431;
	data->col_floor = 33554431;
	data->map = NULL;
	return (0);
}
