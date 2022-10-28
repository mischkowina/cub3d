#include "../cub3d.h"

int	map[MAP_WIDTH][MAP_HEIGHT] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int	main(int argc, char **argv)
{
	t_data	data;

	argc = 1;
	argv[0][0] = 'a';

	init(&data);
	handle_player(&data);
	mlx_hook(data.win, 17, 0, &close_x, &data); // exits the program when x is clicked
	mlx_key_hook(data.win, &key_hooks, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
}

// this functions is creating the window and filling it with colors
void	init(t_data *data)
{
// here I initialize the position of the player that gets later changed with WASD
	data->pos_x = 230;
	data->pos_y = 160;
// initialize the player angle to 2 * PI
	data->p_angle = PI / 2;
	data->pdx = cos(data->p_angle) * 5;
	data->pdy = sin(data->p_angle) * 5;

	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return ;
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, \
	&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_grid(data);
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
			y = data->img.px_y / 72;
			x = data->img.px_x / 72;
			if (map[x][y] == 1)
				color = LIGHT_PINK;
			else if (map[x][y] == 0)
				color = BLACK;
			if ((data->img.px_x % 72 == 0 || data->img.px_y % 72 == 0) \
				&& data->img.px_x != 0 && data->img.px_y != 0)
				color = WHITE;
			pixel_put(data, color);
			data->img.px_x++;
		}
		data->img.px_y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void	handle_player(t_data *data)
{
	draw_grid(data);
	draw_point(data);
	draw_line(data);
}