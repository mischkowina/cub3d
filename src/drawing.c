
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
	start_x = data->pos.x - size;
	start_y = data->pos.y - size;
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

void	draw_line(int x0, int y0, int x1, int y1, t_data * data) // this is the best one so far
{
	double	dx;
	double	dy;
	double	px_x;
	double	px_y;
	int		px;

	dx = x1 - x0;
	dy = y1 - y0;
	px = sqrt((dx * dx) + (dy * dy));
	dx /= px;
	dy /= px;
	px_x = x0;
	px_y = y0;
	while (px)
	{
		data->img.px_x = px_x;
		data->img.px_y = px_y;
		pixel_put(data, YELLOW);
		px_x += dx;
		px_y += dy;
		px--;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

// void	draw_line(double x0, double y0, double x1, double y1, t_data *data) // this is the working one
// {
// 	double	dx;
// 	double	dy;
// 	double	pk;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	pk = 2 * (dy - dx);
// 	if (dx >= 0 && dy >= 0)
// 	{
// 		printf("AAAAAAA\n");
// 		while (x0 <= x1)
// 		{
// 			data->img.px_x = x0;
// 			data->img.px_y = y0;
// 			pixel_put(data, YELLOW);
// 			if (pk < 0)
// 				pk += 2 * dy;
// 			else
// 			{
// 				y0++;
// 				pk += 2 * (dy - dx);
// 			}
// 			x0++;
// 		}
// 	}
// 	else if (dx < 0 && dy > 0)
// 	{
// 		printf("BBBBBB\n");
// 		while (x0 >= x1)
// 		{
// 			data->img.px_x = x0;
// 			data->img.px_y = y0;
// 			pixel_put(data, YELLOW);
// 			if (pk < 0)
// 				pk += 2 * dy;
// 			else
// 			{
// 				y0++;
// 				pk += 2 * (dy - dx);
// 			}
// 			x0--;
// 		}
// 	}
// 	else if (dx > 0 && dy < 0)
// 	{
// 		printf("CCCCCC\n");
// 		while (x0 <= x1)
// 		{
// 			data->img.px_x = x0;
// 			data->img.px_y = y0;
// 			pixel_put(data, YELLOW);
// 			if (pk < 0)
// 				pk += 2 * dy;
// 			else
// 			{
// 				y0--;
// 				pk += 2 * (dy - dx);
// 			}
// 			x0++;
// 		}
// 	}
// 	else if (dx < 0 && dy < 0)
// 	{
// 		printf("DDDDDDD\n");
// 		while (x0 >= x1)
// 		{
// 			data->img.px_x = x0;
// 			data->img.px_y = y0;
// 			pixel_put(data, YELLOW);
// 			if (pk < 0)
// 				pk += 2 * dy;
// 			else
// 			{
// 				y0--;
// 				pk += 2 * (dy - dx);
// 			}
// 			x0--;
// 		}
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }

// void	draw_line(int x0, int y0, int dx, int dy, t_data *data)
// {
// 	int	x1;
// 	int	y1;
// 	int	pk;

// 	dx *= 10;
// 	dy *= 10;
// 	pk = 2 * dy - dx;
// 	x1 = x0 + dx;
// 	y1 = y0 + dy;
// 	printf("dx: %d, dy: %d, x0: %d, y0: %d, x1: %d, y1: %d\n", dx, dy, x0, y0, x1, y1);
// 	while (x0 <= x1)
// 	{
// 		data->img.px_x = x0;
// 		data->img.px_y = y0;
// 		pixel_put(data, YELLOW);
// 		if (pk < 0)
// 			pk += 2 * dy;
// 		else
// 		{
// 			y0++;
// 			pk += 2 * (dy - dx);
// 		}
// 		x0++;
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }

// void	draw_line(t_data *data)
// {
// 	float	m;
// 	float	c;
// 	int		x1;
// 	int		y1;
// 	float	temp_y;
// 	int		i = 0;

// 	x1 = data->pos_x + (2 * data->pdx);
// 	y1 = data->pos_y + (2 * data->pdy);
// 	m = (y1 - data->pos_y) / (x1 - data->pos_x);
// 	c = data->pos_y - (m * data->pos_x);
// 	data->img.px_x = data->pos_x;
// 	while (i < data->pdx)
// 	{
// 		temp_y = (m * data->pos_x) + c;
// 		printf("temp y = %f\n", temp_y);
// 		data->img.px_y = round(temp_y);
// 		pixel_put(data, YELLOW);
// 		data->img.px_x++;
// 		i++;
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
// }

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