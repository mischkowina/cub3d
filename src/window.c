
#include "../cub3d.h"

// function puts a pixel of given color into given coordinates that 
// are in the data struct
void	pixel_put(t_data *data, int color)
{
	char	*dst;

	dst = data->img.addr + (data->img.px_y * data->img.line_length + \
	data->img.px_x * (data->img.bpp / 8));
	*(unsigned int*)dst = color;
}

//function that does what needs to be done if a key is pressed
int	key_hooks(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_x(data);
	if (keycode == KEY_W)
		w_key_pressed(data);
	if (keycode == KEY_A)
		a_key_pressed(data);
	if (keycode == KEY_S)
		s_key_pressed(data);
	if (keycode == KEY_D)
		d_key_pressed(data);
	if (keycode == KEY_LEFT)
		rotate(data, ROT_ANGLE);
	if (keycode == KEY_RIGHT)
		rotate(data, -ROT_ANGLE);
	if (keycode == KEY_SPACE)
		open_door(data);
	return (0);
}

int	mouse_rotation(int x, int y, t_data *data)
{
	double	rotation_speed;

	(void)y;
	rotation_speed = ROT_ANGLE / 5;
	mlx_mouse_move(data->win, data->mouse.x, data->mouse.y);
	if (x < data->mouse.x) // rotate to the left
		rotate(data, rotation_speed);
	else if (x > data->mouse.x) // rotate to the right
		rotate(data, -rotation_speed);
	return (0);
}

//function that closes the window and exits the program
int	close_x(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	exit(0);
}