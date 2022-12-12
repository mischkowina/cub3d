#include "../cub3d.h"

void	draw_player(int x, int y, t_data *data, int color)
{
	int	start_x;
	int	start_y;
	int	size;

	size = 5;
	start_x = x - size;
	start_y = y - size;
	data->img.px_y = start_y;
	// data->img.px_y = y;
	while (data->img.px_y < start_y + size)
	{
		data->img.px_x = x;
		while (data->img.px_x < start_x + size)
		{
			pixel_put(data, color);
			data->img.px_x++;
		}
		data->img.px_y++;
	}
	// mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

// void	draw_point(int x, int y, t_data *data, int color)
// {
// 	// int	start_x;
// 	// int	start_y;
// 	int	size;

// 	size = 15;
// 	// start_x = x - size;
// 	// start_y = y - size;
// 	// data->img.px_y = start_y;
// 	data->img.px_y = y;
// 	while (data->img.px_y < y + size)
// 	{
// 		data->img.px_x = x;
// 		while (data->img.px_x < x + size)
// 		{
// 			pixel_put(data, color);
// 			data->img.px_x++;
// 		}
// 		data->img.px_y++;
// 	}
// 	// mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }

void	render_minimap(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	// data->img.px_y = 10; //a coordinate where I want to start the minimap
	while (y < data->height_map)
	{
		// data->img.px_x = 10; //a coordinate where I want to start the minimap
		x = 0;
		while (x < data->width_map) // where I want to stop the minimap
		{
			if (data->map[y][x] == 1)
				color = LIGHT_PINK;
			else if (data->map[y][x] == 0)
				color = BLACK;
			else if (data->map[y][x] == 3)
				color = RED;
			draw_point(x * 16 + 10, y * 16 + 10, data, color);
			x++;
		}
		y++;
	}
	draw_player(data->pos.x * 16 + 10, data->pos.y * 16 + 10, data, YELLOW);
	// mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}