
#include "../cub3d.h"

//function draws the point based on the posx posy saved in data struct
void	draw_point(t_data *data)
{
	int	start_x;
	int	start_y;
	int	size;
	int	color;

	size = 10;
	color = YELLOW;
	start_x = data->pos_x - size;
	start_y = data->pos_y - size;
	data->img.px_y = start_y;
	while (data->img.px_y < start_y + size)
	{
		data->img.px_x = start_x;
		while (data->img.px_x < start_x + size)
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
	float	m;
	float	c;
	int		x1;
	int		y1;
	float	temp_y;
	int		i = 0;

	x1 = data->pos_x + (2 * data->pdx);
	y1 = data->pos_y + (2 * data->pdy);
	m = (y1 - data->pos_y) / (x1 - data->pos_x);
	c = data->pos_y - (m * data->pos_x);
	data->img.px_x = data->pos_x;
	while (i < data->pdx)
	{
		temp_y = (m * data->pos_x) + c;
		printf("temp y = %f\n", temp_y);
		data->img.px_y = round(temp_y);
		pixel_put(data, YELLOW);
		data->img.px_x++;
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

// void	draw_line(t_data *data)
// {
// 	int	x0;
// 	int	y0;
// 	int	dx;
// 	int	dy;
// 	int	p;

// 	x0 = data->pos_x;
// 	y0 = data->pos_y;
// 	dx = data->pdx * 3;
// 	dy = data->pdy * 3;
// 	p = 2 * dy - dx;
// 	data->img.px_x = data->pos_x;
// 	data->img.px_y = data->pos_y;
// 	while (data->img.px_x < data->img.px_x + dx)
// 	{
// 		if (p >= 0)
// 		{
// 			pixel_put(data, YELLOW);
// 			data->img.px_y++;
// 			p = p + (2 * data->pdy) - (2 * data->pdx);
// 		}
// 		else
// 		{
// 			pixel_put(data, YELLOW);
// 			p = p + (2 * data->pdy);
// 		}
// 		data->img.px_x++;
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }

// void	draw_line(t_data *data)
// {
// 	float	ratio;

// 	if (data->pdx > data->pdy)
// 	{
// 		ratio = data->pdx / data->pdy;
// 		while (data->pos_x < data->pos_x + data->pdx)
// 		{
// 			data->pdy += ratio;
// 			while (data->pos_y < data->pdy + ratio)
// 			{
// 				pixel_put(data, YELLOW);
// 				data->pos_y++;
// 			}
// 			data->pos_x++;
// 		}
// 	}
// 	else if (data->pdy > data->pdx)
// 	{
// 		ratio = data->pdy / data->pdx;
// 		while (data->pos_y < data->pos_y + data->pdy)
// 		{
// 			while (data->pos_x < data->pdx + ratio)
// 			{
// 				pixel_put(data, YELLOW);
// 				data->pos_x++;
// 			}
// 			data->pos_y++;
// 		}
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }