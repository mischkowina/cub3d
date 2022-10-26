#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	check_input(argc, argv);
	parser(argv[1], &data);
	return (0);
}

int	check_input(int argc, char **argv)
{
	//INFO: check number of arguments
	if (argc != 2)
	{
		if (argc < 2)
			ft_error("ERROR: .cub file as argument required.");
		else
			ft_error("ERROR: Only argument allowed.");
	}
	//INFO: check if argument ends with .cub
	else if (ft_strncmp((argv[1] + ft_strlen(argv[1] - 4)), ".cub", 5))
		ft_error("ERROR: .cub file as argument required.");
	return (0);
}

int	parser(char *file, t_data *data)
{
	int		fd;
	char	*line;

	//INFO: open the .cub file and see if it is readable
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(NULL);
	//INFO: iterate through the file and parse the information
	line = get_next_line(fd);//has to be freed
	while (line)//OPEN: maybe second condition (line[0] != 1 or 0??)
	{
		if (ft_strncmp(line, "NO", 2))
			//OPEN: parse line, remove identifier & spaces
	}
	return (0);
}

void	ft_error(char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	else
		perror("ERROR: ");
	//OPEN: anything to be done before exit (mlx_destroy window, ...)?
	exit(0);//OPEN: any reason for another exit code?
}
