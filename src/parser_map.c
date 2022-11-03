#include "../cub3d.h"

int	parse_map(t_data *data, char *line, int fd)
{
	char	*map_str;
	char	*tmp;

	check_prev_input(data);
	map_str = ft_strdup("");
	while (line && (!ft_strncmp(line, " ", 1) || !ft_strncmp(line, "1", 1)))
	{
		tmp = map_str;
		//free(map_str);//TEST WITH THIS LINE???
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
	int		row;
	int		i;
	size_t	max_width;
	
	max_width = 0;
	row = 0;
	i = 0;
	map_rows = ft_split(map_str, '\n');//TEST: is a \n at the end of the map removed?
	if (!map_rows || !ft_strncmp(map_rows[0], "", 1))
		ft_error("Invalid input for map.");
	free(map_str);
	while (map_rows[row])
	{
		if (ft_strlen(map_rows[row]) > max_width)
			max_width = ft_strlen(map_rows[row]);
		row++;
	}
	data->height_map = row;
	data->width_map = (int) max_width;
	data->map = ft_calloc(sizeof(int*), row);
	if (!data->map)
		ft_error("Allocation of map failed.");
	while (i < row)
	{
		data->map[i] = ft_calloc(sizeof(int), data->width_map);
		if (!data->map[i++])
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
		while (i < data->width_map)
			data->map[row][i++] = -1;
		row++;
	}
	free_str_arr(map_rows);
	return (0);
}

int	check_map_array(t_data *data)
{
	int	row;
	int	col;
	int	pos;

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
