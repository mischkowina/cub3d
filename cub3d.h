
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
// # include "/usr/X11/include/X11/X.h"
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>
# include <stdbool.h>

# define WIDTH 			1440
# define HEIGHT			720

# define KEY_ESC		53
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define MAP_WIDTH		10
# define MAP_HEIGHT		10

# define PLAYER_SIZE	10

# define BLACK			0x000000
# define WHITE			0xFFFFFF
# define GREY			0xA1A1A1
# define PINK			0x0F542D4
# define LIGHT_PINK		0xa3819c
# define BRIGHT_PINK	0xE6AEDB
# define YELLOW			0xFFDF07
# define GREEN			0x00FF00
# define ORANGE			0xFF9933
# define BLUE			0x0099FF
# define RED			0xFF0000

# define PI				3.1415926535

# define FOV_D			60
# define FOV			M_PI / 180 * FOV_D
# define ROT_ANGLE		M_PI / 36.0

int	map[MAP_WIDTH][MAP_HEIGHT];

typedef struct s_trgb
{
	int	t;
	int	r;
	int	g;
	int	b;
}				t_trgb;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
	int		px_x;
	int		px_y;
}				t_img;

typedef struct s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_trgb	trgb;
	t_vec	pos;
	t_vec	dir;
	t_vec	camera_plane;
	char	player_dir;
	float	p_angle;
	float	pdx;
	float	pdy;
}				t_data;

typedef struct s_delta
{
	double	dx;
	double	dy;
	double	angle;
	double	small_ray;
}				t_delta;

typedef struct s_ray
{
	bool	done;
	double	hor_grid;
	double	ver_grid;
	t_delta	hor;
	t_delta	ver;
	double	dir_x;
	double	dir_y;
	double	angle;
	double	horizontal_line;
	double	vertical_line;
}				t_ray;

// main.c //
void	init(t_data *data);
void	draw_grid(t_data *data);
void	handle_player(t_data *data);

// window.c //
void	pixel_put(t_data *data, int color);
int		key_hooks(int keycode, t_data *data);
int		close_x(t_data *data);

// drawing.c //
// void	draw_point(t_data *data);
// void	draw_point(int x, int y, t_data *data);
void	draw_point(int x, int y, t_data *data, int color);
void	draw_line(int x0, int y0, int x1, int y1, t_data *data, int color);
// void	draw_line(double x0, double y0, double x1, double y1, t_data *data); // this is the working one
// void	draw_line(t_data *data);
// void	draw_line(int x0, int y0, int dx, int dy, t_data *data);

// keys.c //
void	w_key_pressed(t_data *data);
void	a_key_pressed(t_data *data);
void	s_key_pressed(t_data *data);
void	d_key_pressed(t_data *data);
void	left_key_pressed(t_data *data);
void	right_key_pressed(t_data *data);

// math.c //
void	find_vector_values(t_vec *vec, double angle);
void	normalize_vector(t_vec *vec);
void	perpendicular_vector(t_vec *vec);

// init.c //
void	init_orientation(t_data *data);

// ray.c //
void	cast_ray(t_data *data);
void	find_nearest_grid(t_ray *ray, t_data *data);

#endif
