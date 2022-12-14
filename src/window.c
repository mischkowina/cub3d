
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
	if (keycode == 53)
		close_x(data);
	else if (keycode == 13)
		w_key_pressed(data);
	else if (keycode == 0)
		a_key_pressed(data);
	else if (keycode == 1)
		s_key_pressed(data);
	else if (keycode == 2)
		d_key_pressed(data);
	else if (keycode == 123)
		rotate(data, -data->rotation_speed);
	else if (keycode == 124)
		rotate(data, data->rotation_speed);
	else if (keycode == 49)
		if (data->guns_out == 0)
			open_door(data);
		else
		{
			data->guns_shot = 1;
			play_sound("sounds/gun_shot.m4a");
		}
	else if (keycode == 257 || keycode == 258)
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