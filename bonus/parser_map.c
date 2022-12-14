/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:56:11 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 14:15:24 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Function to iterate through the map-part of the .cub file and processes 
 * the content line by line into one long string.
 * Returns error if it finds any invalid input within or after the map.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @param line [char *] First line of the map input.
 * @param fd [fd] File descriptor of the .cub file.
*/
void	parse_map(t_data *data, char *line, int fd)
{
	char	*map_str;
	char	*tmp;

	check_prev_input(data);
	map_str = ft_strdup("");
	while (line && (!ft_strncmp(line, " ", 1) || !ft_strncmp(line, "1", 1)))
	{
		tmp = map_str;
		map_str = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	while (line && !ft_strncmp(line, "\n", ft_strlen(line)))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line || !ft_strncmp(map_str, "", 1))
		ft_error("Invalid input for map.", data);
	close(fd);
	fill_map_array(data, map_str);
	check_map_array(data);
}

/**
 * Function to check if all necessary input has been given before the map
 * gets parsed.
 * @param data [t_data *] Pointer to struct storing the input data.
*/
void	check_prev_input(t_data *data)
{
	if (!data->n_texture.filename || !data->e_texture.filename
		|| !data->s_texture.filename || !data->w_texture.filename)
		ft_error("Incomplete input for textures.", data);
	else if (data->col_ceiling == -1 || data->col_floor == -1)
		ft_error("Incomplete input for colors.", data);
}

/**
 * Function to transfer the map input into a 2D integer array. First allocates 
 * enough space for the integer array, then it iterates through the string array
 * representing the map in characters and checks the input as well as transfers
 * it to the int array.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @param map_str [char *] String containing the total map data.
*/
void	fill_map_array(t_data *data, char *map_str)
{
	char	**map_rows;
	int		row;
	int		col;

	row = 0;
	col = 0;
	map_rows = ft_split(map_str, '\n');
	free(map_str);
	allocate_map_array(data, map_rows);
	while (map_rows[row])
	{
		col = 0;
		while (map_rows[row][col])
		{
			if (copy_map_tile(map_rows[row][col], row, col, data))
				ft_error("Invalid input for map.", data);
			col++;
		}
		while (col < data->width_map)
			data->map[row][col++] = -1;
		row++;
	}
	allocate_doors_sprites(data);
	free_str_arr(map_rows);
}

/**
 * Function to fill a single field of the 2D integer array with the integer 
 * representation of the given character.
 * Map explanation:
 * -1 = empty space outside walls (' ')
 * 1 = wall
 * 0 = empty space within walls
 * 2 = player position
 * 3 = door positions
 * 4 = mummy positions
 * 5 = sarcophagus ("tut") positions
 * 6 = chest positions
 * @param c [char] Character to be transfered into the int array.
 * @param row [int] Row position of the respective array field.
 * @param col [int] Column position of the respective array field.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [int] 0 if c is a valid input and has been processed, else 1.
*/
int	copy_map_tile(char c, int row, int col, t_data *data)
{
	if (c == ' ')
		data->map[row][col] = -1;
	else if (c == '1')
		data->map[row][col] = 1;
	else if (c == '0')
		data->map[row][col] = 0;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		copy_player_position(data, col, row, c);
	else if (c == 'D')
	{
		if (!data->d_texture.filename)
			ft_error("No texture input for doors.", data);
		else
		{
			data->map[row][col] = 3;
			data->nbr_doors++;
		}
	}
	else if (parse_sprites(c, row, col, data) > 0)
		return (1);
	return (0);
}

void	copy_player_position(t_data *data, int col, int row, char c)
{
	data->map[row][col] = 2;
	data->pos.x = col;
	data->pos.y = row;
	data->player_dir = c;
}
