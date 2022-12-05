
#include "../cub3d.h"

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
		if (data->map[row][col] == 3)
		{
			data->doors[data->door_counter]->col = col;
			data->doors[data->door_counter++]->row = row;
		}
		if (data->map[row][col] > 3 && data->map[row][col] < 7)
			fill_sprite(data, row, col);
	}
}
