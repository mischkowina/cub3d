
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
# define KEY_SPACE		49

typedef struct s_data {
	char	*filename;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_door {
	int		col;
	int		row;
	int		opening;
	int		closed;
	int		cur_width;
}				t_door;

typedef struct s_ray {
	int		x;
	double	dist;
}				t_ray;

typedef	struct s_cub
{
	t_data	N_texture;
	t_data	E_texture;
	t_data	S_texture;
	t_data	W_texture;
	t_data	D_texture;
	int		col_ceiling;
	int		col_floor;
	int		**map;
	int		width_map;
	int		height_map;
	char	player_dir;
	int		player_pos_x;
	int		player_pos_y;
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
	int		nbr_doors;
	int		door_counter;
	t_door	**doors;
	t_ray	*cur_ray;
	t_data	**mummy;
}				t_cub;

int		check_input(int argc, char **argv);
int		init_data(t_cub *data);
int		test_textures(t_cub *data);//TEST FUNCTION; TO BE REPLACED
int		render(t_cub *data);//TEST FUNCTION; TO BE REPLACED
int		handle_keypress(int key, t_cub *data);//TEST FUNCTION, TO BE REPLACED

void	parser(char *file, t_cub *data);
int		parse_info_type(t_cub *data, char *line);
char	*parse_texture(char *line);
int		parse_color(char *line);
int		determine_color_value(char **split);

void	parse_map(t_cub *data, char *line, int fd);
void	check_prev_input(t_cub *data);
void	fill_map_array(t_cub *data, char *map_str);
void	allocate_map_array(t_cub *data, char **map_rows);
int		copy_map_tile(char c, int row, int col, t_cub *data);

void	check_map_array(t_cub *data);
void	check_tile(t_cub *data, int row, int col, int *pos);

void	ft_mlx_pixel_put(t_data *img, int x, int y, int color);
void	prep_image(t_cub *data);
void	draw_wall(t_cub *data, t_data *texture);

void	open_texture(t_cub *data, t_data *texture);
void	open_all_textures(t_cub *data);
int		get_texture_color(int x, int y, t_data *texture);

void	allocate_doors(t_cub *data);
void	draw_door(t_cub *data, t_door *door, double tex_pos_x);
void	open_door(t_cub *data);
void	check_door_opening(t_cub *data);

void	init_sprites(t_cub *data);
double	draw_sprites(t_cub *data, double tex_pos_x);

int		str_is_digit(char *str);
void	free_str_arr(char **str);
void	ft_error(char *msg);

#endif
