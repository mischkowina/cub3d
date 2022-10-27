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
		while (!ft_strncmp(line, "\n", ft_strlen(line)))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (line && !ft_strncmp(line, "NO ", 3))
			data->N_texture = parse_texture(line);
		else if (line && !ft_strncmp(line, "EA ", 3))
			data->E_texture = parse_texture(line);
		else if (line && !ft_strncmp(line, "SO ", 3))
			data->S_texture = parse_texture(line);
		else if (line && !ft_strncmp(line, "WE ", 3))
			data->W_texture = parse_texture(line);
		else if (line && !ft_strncmp(line, "F ", 2))
			data->col_floor = parse_color(line);
		else if (line && !ft_strncmp(line "C "))
			data->col_ceiling = parse_color(line);
		//OPEN: else map / invalid input <--- HERE
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

//creates substring without the identifier and the /n at the end
char	*parse_texture(char *line)
{
	int		i;
	char	*str;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (NULL);//OPEN: this or error message?
	str = ft_substr(line, i, (ft_strlen(line) - 1 - i));
	return(str);
}

int	parse_color(char *line)
{
	int		i;
	char	**split;
	char	*tmp;

	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		ft_error("ERROR: Invalid input for floor / ceiling color.");//OPEN: this or return value?
	split = ft_split(line, ',');
	if (!split || !split[0])
		ft_error("ERROR: Invalid input for floor / ceiling color.");//OPEN: this or return value?
	i = 0;
	while (split[i])
	{
		tmp = ft_strtrim(split[i], " \n");
		free(split[i]);
		split[i] = tmp;
		i++;
	}
	if (i != 3)
		ft_error("ERROR: Invalid input for floor / ceiling color.");//OPEN: this or return value?
	return (determine_color_value(split));
}

int	determine_color_value(char **split)
{
	int	c[3];
	int	i;

	i = 0;
	while (split[i])
	{
		if (!str_is_digit(split[i]))
			ft_error("ERROR: Invalid input for floor / ceiling color.");//OPEN: this or return value?
		c[i] = ft_atoi(split[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (c[i] < 0 || c[i] > 255)
			ft_error("ERROR: Invalid input for floor / ceiling color.");//OPEN: this or return value?
		i++;
	}
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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
