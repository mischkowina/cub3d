/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:39:38 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 19:54:02 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Function to allocate sufficient memory space for the 2D integer array
 * representing the map.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @param map_rows [char **] String array containing the map data.
*/
void	allocate_map_array(t_data *data, char **map_rows)
{
	int		row;
	int		i;
	size_t	max_width;

	max_width = 0;
	row = 0;
	i = 0;
	while (map_rows[row])
	{
		if (ft_strlen(map_rows[row]) > max_width)
			max_width = ft_strlen(map_rows[row]);
		row++;
	}
	data->height_map = row;
	data->width_map = (int) max_width;
	data->map = ft_calloc(sizeof(int *), row + 1);
	if (!data->map || row == 0 || max_width == 0)
		ft_error("Allocation of map failed.", data);
	while (i < row)
	{
		data->map[i] = ft_calloc(sizeof(int), data->width_map);
		if (!data->map[i++])
			ft_error("Allocation of map failed.", data);
	}
}

/**
 * Checks the map input tile by tile for open walls and unambiguous 
 * starting position.
 * @param data [t_cub *] Pointer to struct storing all the input data.
*/
void	check_map_array(t_data *data)
{
	int	row;
	int	col;
	int	pos;

	row = 0;
	col = 0;
	pos = 0;
	while (row < data->height_map)
	{
		col = 0;
		while (col < data->width_map)
			check_tile(data, row, col++, &pos);
		row++;
	}
	if (pos != 1)
		ft_error("Invalid input for map: unclear starting position.", data);
}

/**
 * Checks for "inside" map tiles (so doors, player position and empty spaces)
 * if they are adjacent to a "outside tile" (-1 space outside of walls).
 * If so, there is an open wall in the map and the respective error is shown.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param row [int] Row position of the respective map tile.
 * @param col [int] Column position of the respective map tile.
 * @param pos [int *] Pointer to the int storing the number of player positions.
*/
void	check_tile(t_data *data, int row, int col, int *pos)
{
	if (data->map[row][col] == 0 || data->map[row][col] >= 2)
	{
		if (col > 0 && data->map[row][col - 1] < 0)
			ft_error("Invalid input for map: open walls.", data);
		if (col < (data->width_map - 1) && data->map[row][col + 1] < 0)
			ft_error("Invalid input for map: open walls.", data);
		if (row > 0 && data->map[row - 1][col] < 0)
			ft_error("Invalid input for map: open walls.", data);
		if (row < (data->height_map - 1) && data->map[row + 1][col] < 0)
			ft_error("Invalid input for map: open walls.", data);
		if (data->map[row][col] == 2)
		{
			data->pos.x = col;
			data->pos.y = row;
			(*pos)++;
		}
	}
}

int	check_if_accessible(t_data *data, int x, int y)
{
	if (data->map[y][x] == 0 || data->map[y][x] == 2 || data->map[y][x] > 3)
		return (1);
	return (0);
}
