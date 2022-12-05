#include "../cub3d.h"

// int	map[MAP_HEIGHT][MAP_WIDTH] =
// {
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
// 	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1}, 
// 	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

int	main(int argc, char **argv)
{
	t_data	data;

	argc = 1;
	argv[0][0] = 'a';

	init(&data);
	draw_minimap(&data);
	draw_floor_and_ceiling(&data);
	raycasting(&data);
	mlx_hook(data.win, 17, 0, &close_x, &data); // exits the program when x is clicked
	mlx_key_hook(data.win, &key_hooks, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
}

// function interprets the 2d array and draws white squares for walls and
// black squares for floor, leaving a small gap in between to show grey grid
void	draw_grid(t_data *data)
{
	int				x = 0;
	int				y = 0;
	unsigned int	color;

// the loop iterates through map[][] and draws adequately colored squares
	data->img.px_y = 0;
	while (data->img.px_y < HEIGHT)
	{
		data->img.px_x = 0;
		while (data->img.px_x < (WIDTH / 2))
		{
			y = data->img.px_y / GRID_SIZE;
			x = data->img.px_x / GRID_SIZE;
			if (data->map[y][x] == 1)
				color = LIGHT_PINK;
			else if (data->map[y][x] == 0)
				color = BLACK;
			if ((data->img.px_x % GRID_SIZE == 0 || data->img.px_y % GRID_SIZE == 0) \
				&& data->img.px_x != 0 && data->img.px_y != 0)
				color = WHITE;
			pixel_put(data, color);
			data->img.px_x++;
		}
		data->img.px_y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void	draw_minimap(t_data *data)
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;

	x0 = data->pos.x;
	y0 = data->pos.y;
	x1 = data->pos.x + (data->dir.x * 20);
	y1 = data->pos.y + (data->dir.y * 20);
	draw_grid(data);
// draw player //
	draw_point(data->minimap.pos.x, data->minimap.pos.y, data, YELLOW);
// draw player direction //
	draw_line(data->minimap.pos.x - 5, data->minimap.pos.y - 5, data->minimap.pos.x - 5 + (data->dir.x * 100), data->minimap.pos.y - 5 + (data->dir.y * 100), data, YELLOW);
// draw camera plane vector //
	draw_line(data->minimap.pos.x - 5 + (data->dir.x * 20), data->minimap.pos.y - 5 + (data->dir.y * 20), data->minimap.pos.x - 5 + (data->dir.x * 20) + (data->camera_plane.x * 20),  data->minimap.pos.y - 5 + (data->dir.y * 20) + (data->camera_plane.y * 20), data, GREEN);
	draw_line(data->minimap.pos.x - 5 + (data->dir.x * 20), data->minimap.pos.y - 5 + (data->dir.y * 20), data->minimap.pos.x - 5 + (data->dir.x * 20) - (data->camera_plane.x * 20),  data->minimap.pos.y - 5 + (data->dir.y * 20) - (data->camera_plane.y * 20), data, GREEN);
}

