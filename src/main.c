#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	check_input(argc, argv);
	init_data(&data);
	parser(argv[1], &data);
	printf("N_texture: %s\n", data.N_texture);
	printf("E_texture: %s\n", data.E_texture);
	printf("S_texture: %s\n", data.S_texture);
	printf("W_texture: %s\n", data.W_texture);
	printf("col_ceiling: %d\n", data.col_ceiling);
	printf("col_floor: %d\n", data.col_floor);
	printf("width_map: %d\n", (int) data.width_map);
	printf("height_map: %d\n", (int) data.height_map);
	printf("player_dir: %c\n", data.player_dir);
	return (0);
}

int	check_input(int argc, char **argv)
{
	//INFO: check number of arguments
	if (argc != 2)
	{
		if (argc < 2)
			ft_error(".cub file as argument required.");
		else
			ft_error("Only one argument allowed.");
	}
	//INFO: check if argument ends with .cub
	if (ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 5))
		ft_error(".cub file as argument required.");
	return (0);
}

int	init_data(t_data *data)
{
	data->N_texture = NULL;
	data->E_texture = NULL;
	data->S_texture = NULL;
	data->W_texture = NULL;
	data->col_ceiling = 33554431;//not possible to be a color when t is 0
	data->col_floor = 33554431;//not possible to be a color when t is 0
	data->map = NULL;
	return (0);
}

void	ft_error(char *msg)
{
	if (msg)
		printf("Error\n%s\n", msg);
	else
		perror("Error");
	//OPEN: anything to be done before exit (mlx_destroy window, ...)?
	exit(0);//OPEN: any reason for another exit code?
}
