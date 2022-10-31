#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	check_input(argc, argv);
	init_data(&data);
	parser(argv[1], &data);
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
	else if (ft_strncmp((argv[1] + ft_strlen(argv[1] - 4)), ".cub", 5))
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
}

void	ft_error(char *msg)
{
	if (msg)
	{
		write(2, "Error\n", ft_strlen(msg));
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}	
	else
		perror("Error\n");
	//OPEN: anything to be done before exit (mlx_destroy window, ...)?
	exit(0);//OPEN: any reason for another exit code?
}
