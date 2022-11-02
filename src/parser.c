
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
	printf("TEST after loop\n");
	if (line && (!ft_strncmp(line, " ", 1) || !ft_strncmp(line, "1", 1)))
		parse_map(data, line, fd);
	else if (line)
		ft_error("Invalid input in .cub file.");
	else
		ft_error("No valid map in .cub file.");
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
		ft_error("Texture input missing");
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
		ft_error("Invalid input for floor / ceiling color.");
	tmp = ft_substr(line, i, ft_strlen(line));
	split = ft_split(tmp, ',');
	free(tmp);
	if (!split || !split[0])
		ft_error("Invalid input for floor / ceiling color.");
	i = 0;
	while (split[i])
	{
		printf("split[%d]: %s\n", i, split[i]);
		tmp = ft_strtrim(split[i], " \n");
		free(split[i]);
		split[i] = tmp;
		i++;
	}
	if (i != 3)
		ft_error("Invalid input for floor / ceiling color.");
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
			ft_error("Invalid input for floor / ceiling color.");
		c[i] = ft_atoi(split[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (c[i] < 0 || c[i] > 255)
			ft_error("Invalid input for floor / ceiling color.");
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
	while (line && (!ft_strncmp(line, " ", 1) || !ft_strncmp(line, "1", 1)))
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
	check_map_array(data);
	return (0);
}

int	check_prev_input(t_data *data)
{
	if (!data->N_texture || !data->E_texture 
		|| !data->S_texture || !data->W_texture)
		ft_error("Incomplete input for textures.");
	else if (data->col_ceiling == 33554431 || data->col_floor == 33554431)
		ft_error("Incomplete input for colors.");
	return (0);
}

int	fill_map_array(t_data *data, char *map_str)
{
	char	**map_rows;
	size_t	max_width;
	size_t	row;
	size_t	i;
	
	max_width = 0;
	row = 0;
	i = 0;
	map_rows = ft_split(map_str, '\n');//TEST: is a \n at the end of the map removed?
	if (!map_rows || ft_strncmp(map_rows[0], "", 1))
		ft_error("Invalid input for map.");
	free(map_str);
	while (map_rows[row])
	{
		if (ft_strlen(map_rows[row]) > max_width)
			max_width = ft_strlen(map_rows[row]);
		row++;
	}
	data->width_map = max_width;
	data->width_map = row;
	data->map = ft_calloc(sizeof(int*), row);
	if (!data->map)
		ft_error("Allocation of map failed.");
	while (i < row)
	{
		data->map[i] = ft_calloc(sizeof(int), max_width);
		if (!data->map[i])
			ft_error("Allocation of map failed.");
	}
	row = 0;
	while (map_rows[row])
	{
		i = 0;
		while (map_rows[row][i])
		{
			if (map_rows[row][i] == ' ')
				data->map[row][i] = -1;
			else if (map_rows[row][i] == '1')
				data->map[row][i] = 1;
			else if (map_rows[row][i] == '0')
				data->map[row][i] = 0;
			else if (map_rows[row][i] == 'N' || map_rows[row][i] == 'E'
					||map_rows[row][i] == 'S' || map_rows[row][i] == 'W')
			{
				data->map[row][i] = 2;
				data->player_dir = map_rows[row][i];
			}
			else
				ft_error("Invalid input for map.");
			i++;
		}
		while (i < max_width)
			data->map[row][i++] = -1;
		row++;
	}
	free_str_arr(map_rows);
	return (0);
}

int	check_map_array(t_data *data)
{
	int		row;
	int		col;
	int		pos;

	row = 0;
	col = 0;
	pos = 0;
	while (row < data->height_map)
	{
		while (col < data->width_map)
		{
			if (data->map[row][col] == 0 || data->map[row][col] == 2)
			{
				if (col > 0 && data->map[row][col - 1] < 0)
					ft_error("Invalid input for map: open walls.");
				if (col < (data->width_map - 1) &&  data->map[row][col + 1] < 0)
					ft_error("Invalid input for map: open walls.");
				if (data->map[row][col] == 2)
					pos++;
			}
			col++;
		}
		col = 0;
		row++;
	}
	if (pos != 1)
		ft_error("Invalid input for map: no or ambiguous starting position.");
	row = 0;
	while (col < data->width_map)
	{
		while (row < data->height_map)
		{
			if (data->map[row][col] == 0 || data->map[row][col] == 2)
			{
				if (row > 0 && data->map[row - 1][col] < 0)
					ft_error("Invalid input for map: open walls.");
				if (row < (data->height_map - 1) &&  data->map[row + 1][col] < 0)
					ft_error("Invalid input for map: open walls.");
			}
			row++;
		}
		row = 0;
		col++;
	}
	return (0);
}

void	free_str_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
}
