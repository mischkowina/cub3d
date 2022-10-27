
#include "../cub3d.h"

//function draws the point based on the posx posy saved in data struct
void	draw_point(t_data *data)
{
	int	start_x;
	int	start_y;
	int	size;
	int	color;

	size = 5;
	color = YELLOW;
	start_x = data->pos_x - size;
	start_y = data->pos_y - size;
	data->img.px_y = start_y;
	while (data->img.px_y < start_y + size + size)
	{
		data->img.px_x = start_x;
		while (data->img.px_x < start_x + size + size)
		{
			pixel_put(data, color);
			data->img.px_x++;
		}
		data->img.px_y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void	draw_line(t_data *data)
{
	float	ratio;

	if (data->pdx > data->pdy)
	{
		ratio = data->pdx / data->pdy;
		while (data->pos_x < data->pos_x + data->pdx)
		{
			data->pdy += ratio;
			while (data->pos_y < data->pdy + ratio)
			{
				pixel_put(data, YELLOW);
				data->pos_y++;
			}
			data->pos_x++;
		}
	}
	else if (data->pdy > data->pdx)
	{
		ratio = data->pdy / data->pdx;
		while (data->pos_y < data->pos_y + data->pdy)
		{
			while (data->pos_x < data->pdx + ratio)
			{
				pixel_put(data, YELLOW);
				data->pos_x++;
			}
			data->pos_y++;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}