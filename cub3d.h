
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "/usr/X11/include/X11/X.h"
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

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

# define BLACK			0x000000
# define WHITE			0xFFFFFF
# define GREY			0xA1A1A1
# define PINK			0x0F542D4
# define LIGHT_PINK		0xa3819c
# define BRIGHT_PINK	0xE6AEDB

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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_trgb	trgb;
}				t_data;

void	init(t_data *data);
void	draw_grid(t_data *data);
void	pixel_put(t_data *data, int color);

// window.c //
void	pixel_put(t_data *data, int color);
int		key_hooks(int keycode, t_data *data);
int		close_x(t_data *data);

#endif
