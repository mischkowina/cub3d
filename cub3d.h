
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
# define HEIGHT			1080

# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
//add W, A, S, D

typedef struct s_data {
	char	*filename;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef	struct s_cub
{
	t_data	N_texture;
	t_data	E_texture;
	t_data	S_texture;
	t_data	W_texture;
	int		col_ceiling;
	int		col_floor;
	int		**map;
	int		width_map;
	int		height_map;
	char	player_dir;
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
}				t_cub;

int		check_input(int argc, char **argv);
int		init_data(t_cub *data);

int		parser(char *file, t_cub *data);
int		parse_info_type(t_cub *data, char *line);
char	*parse_texture(char *line);
int		parse_color(char *line);
int		determine_color_value(char **split);

int		parse_map(t_cub *data, char *line, int fd);
int		check_prev_input(t_cub *data);
int		fill_map_array(t_cub *data, char *map_str);
int		check_map_array(t_cub *data);

int		test_textures(t_cub *data);
int		render(t_cub *data);
void	ft_mlx_pixel_put(t_data *img, int x, int y, int color);

int		str_is_digit(char *str);
void	free_str_arr(char **str);
void	ft_error(char *msg);

#endif
