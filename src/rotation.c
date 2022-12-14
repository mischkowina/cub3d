
#include "../cub3d.h"

void	rotate(t_data *data, double angle) //clockwise
{
	double	temp_dir_x;
	double	temp_dir_y;
	double	temp_plane_x;
	double	temp_plane_y;

	temp_dir_x = data->dir.x;
	temp_dir_y = data->dir.y;
	temp_plane_x = data->camera_plane.x;
	temp_plane_y = data->camera_plane.y;
	data->dir.x = cos(angle) * temp_dir_x - sin(angle) * temp_dir_y;
	data->dir.y = sin(angle) * temp_dir_x + cos(angle) * temp_dir_y;
	data->camera_plane.x = cos(angle) * temp_plane_x - sin(angle) * temp_plane_y;
	data->camera_plane.y = sin(angle) * temp_plane_x + cos(angle) * temp_plane_y;
}

int	mouse_rotation(int x, int y, t_data *data)
{
	(void)y;
	mlx_mouse_move(data->win, data->mouse.x, data->mouse.y);
	if (x < data->mouse.x) // rotate to the left
		rotate(data, -data->rotation_speed);
	else if (x > data->mouse.x) // rotate to the right
		rotate(data, data->rotation_speed);
	return (0);
}

long long	time_now(void)
{
	long long		ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	update_move_rot_speeds(t_data *data)
{
	double	frame_time;

	data->old_time = data->new_time;
	data->new_time = time_now();
	frame_time = 1000 / (data->new_time - data->old_time);
	data->move_speed = frame_time / 3500 * 5.0;
	data->rotation_speed = frame_time / 3500 * 1.5;
	data->fps = 1.0 / frame_time;
}
