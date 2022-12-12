#include "../cub3d.h"

void	render_minimap(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	data->img.px_y = 0; //a coordinate where I want to start the minimap
	while (data->img.px_y < HEIGHT)
	{
		data->img.px_x = 0; //a coordinate where I want to start the minimap
		while (data->img.px_x < WIDTH / 2) // where I want to stop the minimap
		{
			if (data->map[y][x] == 1)
				color = LIGHT_PINK;
			else if (data->map[y][x] == 0)
				color = BLACK;
			else if (data->map[y][x] == 3)
				color = RED;
			pixel_put(data, color);
			data->img.px_x++;
		}
		data->img.px_y++;
	}
	// mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}