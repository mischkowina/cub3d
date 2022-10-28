
#include "../cub3d.h"

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
		else if (line && !ft_strncmp(line, "C ", 2))
			data->col_ceiling = parse_color(line);
		else
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line && (!ft_strncmp(line, " ", 1)) || !ft_strncmp(line, "1", 1))
		parse_map(data, line, fd);
	else
		ft_error("Invalid input in .cub file.");
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
		ft_error("Invalid input for floor / ceiling color.");//OPEN: this or return value?
	split = ft_split(line, ',');
	if (!split || !split[0])
		ft_error("Invalid input for floor / ceiling color.");//OPEN: this or return value?
	i = 0;
	while (split[i])
	{
		tmp = ft_strtrim(split[i], " \n");
		free(split[i]);
		split[i] = tmp;
		i++;
	}
	if (i != 3)
		ft_error("Invalid input for floor / ceiling color.");//OPEN: this or return value?
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
			ft_error("Invalid input for floor / ceiling color.");//OPEN: this or return value?
		c[i] = ft_atoi(split[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (c[i] < 0 || c[i] > 255)
			ft_error("Invalid input for floor / ceiling color.");//OPEN: this or return value?
		i++;
	}
	return (0 << 24 | c[0] << 16 | c[1] << 8 | c[2]);
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

int	parse_map(t_data *data, char *line, int fd)
{
	char	*map_str;
	char	*tmp;

	check_prev_input(data);
	map_str = ft_strdup("");
	while (line && (!ft_strncmp(line, " ", 1)) || !ft_strncmp(line, "1", 1))
	{
		tmp = map_str;
		free(map_str);
		map_str = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	while (line && !ft_strncmp(line, "\n", ft_strlen(line)))//OPEN: Do we accept empty newlines at the end of the .cub file?
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		ft_error("Invalid input after map.");
	fill_map_array(data, map_str);
	//check for walls
	//done
}

int	check_prev_input(t_data *data)
{
	if (!data->N_texture || !data->E_texture 
		|| !data->S_texture || !data->W_texture)
		ft_error("Incomplete input for textures.");
	else if (data->col_ceiling == 33554431 || data->col_floor == 33554431)
		ft_error("Incomplete input for colors.");
	else
		return (0);
}

int	fill_map_array(t_data *data, char *map_str)
{
	//split string by \n, remove \n at the very end if necessary
	//determine longest string & number of strings (height and width of map)
	//create int array
	//fill array and check for invalid letters
}