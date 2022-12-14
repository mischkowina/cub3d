
#include "../cub3d.h"

// function puts a pixel of given color into given coordinates that 
// are in the data struct
void	pixel_put(t_img *img, int color)
{
	char	*dst;

	dst = img->addr + (img->px_y * img->line_length + \
	img->px_x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

//function that does what needs to be done if a key is pressed
int	key_hooks(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_x(data);
	else if (keycode == KEY_W)
		w_key_pressed(data);
	else if (keycode == KEY_A)
		a_key_pressed(data);
	else if (keycode == KEY_S)
		s_key_pressed(data);
	else if (keycode == KEY_D)
		d_key_pressed(data);
	else if (keycode == KEY_LEFT)
		rotate(data, -ROT_ANGLE);
	else if (keycode == KEY_RIGHT)
		rotate(data, ROT_ANGLE);
	else if (keycode == KEY_SPACE)
		if (data->guns_out == 0)
			open_door(data);
		else
		{
			data->guns_shot = 1;
			play_sound("sounds/gun_shot.m4a");
		}
	else if (keycode == KEY_SHIFT_L || keycode == KEY_SHIFT_R)
	{
		if (data->guns_out == 0)
		{
			data->guns_out = 1;
			play_sound("sounds/gun_draw.m4a");
		}
		else
		{
			data->guns_down = 1;
			play_sound("sounds/gun_down.m4a");
		}
	}
	return (0);
}

//function that closes the window and exits the program
int	close_x(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	kill_music();
	if (data)
		free_all_shit(data);
	exit(0);
}