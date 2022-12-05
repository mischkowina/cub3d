
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
# include <stdbool.h>

# define WIDTH 			1440
# define HEIGHT			720
# define GRID_SIZE		72

# define KEY_ESC		53
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_SPACE		49
# define MOVESPEED		0.1

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
# define PURPLE			0x9900FF
# define BLUE_SKY		0xb3fcff
# define GREEN_GRASS	0xed2459

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
	void	*img_ptr;//Saskia: rename in my code
	char	*addr;
	int		bits_per_pixel;//Saskia: rename in my code
	int		line_length;
	int		endian;
	int		color;
	int		px_x;
	int		px_y;
	char	*filename;
	int		width;
	int		height;
	double	offset;
	double	size_factor
}				t_img;//Saskia: rename in my code

typedef struct s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct s_vec_int
{
	int		x;
	int		y;
}				t_vec_int;

typedef struct s_minimap
{
	t_vec_int	pos;
}				t_minimap;

typedef struct s_door {
	int		col;
	int		row;
	int		opening;
	int		closed;
	int		cur_width;
	double	tex_pos_x;
}				t_door;

typedef struct s_obj
{
	int		col;
	int		row;
	double	tex_pos_x;
	t_data	*tex;
}				t_obj;

typedef struct s_ray
{
	// this is for a solution from the guide //
	t_vec	dir;
	t_vec	delta_dist;
	int		map_x;
	int		map_y;
	t_vec	side_dist;
	int		step_x;
	int		step_y;
	int		ori;
	double	full_dist;//Saskia: rename in my code
	int		x;//Alina: x-value of the screen width, check if you want to use
	int		nbr_objects;//Alina: count number of object the ray passes
}				t_ray;

typedef struct s_data
{
	t_minimap	map;
	void		*mlx;//Saskia: rename in my code
	void		*win;//Saskia: rename in my code
	t_img		img;//Saskia: rename in my code
	t_trgb		trgb;
	t_vec		pos;//Saskia: set initial player position
	t_vec		dir;
	t_vec		camera_plane;
	char		player_dir;
	float		p_angle;
	float		pdx;
	float		pdy;
	t_ray		*cur_ray;
	int			counter;
	t_data		N_texture;
	t_data		E_texture;
	t_data		S_texture;
	t_data		W_texture;
	t_data		D_texture;
	int			col_ceiling;
	int			col_floor;
	int			**map;
	int			width_map;
	int			height_map;
	int			nbr_doors;
	int			door_counter;
	t_door		**doors;
	int			nbr_sprites;
	int			sprite_counter;
	t_obj		**sprites;
	t_data		**mummy;
	int			cur_mummy;
	t_data		chest;
	t_data		tut;
}				t_data;//Saskia: change type in my code

typedef struct s_delta
{
	int	dx;
	int	dy;
	double	small_ray;
}				t_delta;

	// main.c //
void	draw_grid(t_data *data);
void	draw_minimap(t_data *data);

	// drawing.c //
void	draw_point(int x, int y, t_data *data, int color);
void	draw_line(int x0, int y0, int x1, int y1, t_data *data, int color);
void	draw_floor_and_ceiling(t_data *data);

	// init.c //
void	init(t_data *data);
void	init_minimap(t_data *data);
void	init_orientation(t_data *data);

	// window.c //
void	pixel_put(t_data *data, int color);
int		key_hooks(int keycode, t_data *data);
int		close_x(t_data *data);


	// keys.c //
void	w_key_pressed(t_data *data);
void	s_key_pressed(t_data *data);
void	a_key_pressed(t_data *data);
void	d_key_pressed(t_data *data);
void	right_key_pressed(t_data *data);
void	left_key_pressed(t_data *data);

	// math.c //
void	find_vector_values(t_vec *vec, double angle);
void	normalize_vector(t_vec *vec);
void	perpendicular_vector(t_vec *vec);

	// ray.c //
//--- solution from the guide ---//
void	cast_rays(t_data *data, t_ray *ray, int i);
void	do_the_dda(t_ray *ray);
void	calculate_step(t_data *data, t_ray *ray);
void	paint_my_3d_world(t_ray *ray);
void	raycasting(t_data *data);
//--- my solution ---//
void	cast_the_rays(t_data *data);
void	find_nearest_grid(t_ray *ray, t_data *data);
void	calculate_small_ray(t_ray *ray, t_data *data);

//main.c
int		check_input(int argc, char **argv);
void	init_data(t_cub *data);
void	start_game(t_cub *data);
int		render(t_cub *data);
int		handle_keypress(int key, t_cub *data);//TEST FUNCTION, TO BE INTEGRATED

//parser.c
void	parser(char *file, t_cub *data);
int		parse_info_type(t_cub *data, char *line);
char	*parse_texture(char *line, t_cub *data);
int		parse_color(char *line, t_cub *data);
int		determine_color_value(char **split, t_cub *data);

//parser_map.c
void	parse_map(t_cub *data, char *line, int fd);
void	check_prev_input(t_cub *data);
void	fill_map_array(t_cub *data, char *map_str);
void	allocate_map_array(t_cub *data, char **map_rows);
int		copy_map_tile(char c, int row, int col, t_cub *data);

//check_map.c
void	check_map_array(t_cub *data);
void	check_tile(t_cub *data, int row, int col, int *pos);

//images.c
void	ft_mlx_pixel_put(t_data *img, int x, int y, int color);
void	prep_image(t_cub *data);

//ray.c
void	ray_wall(t_cub *data, t_data *texture);
void	draw_walls(t_cub *data);
void	ray_door(t_cub *data, t_door *door);
void	draw_doors(t_cub *data);
void	ray_sprite(t_cub *data, double dist, t_obj *sprite);
void	draw_sprites(t_cub *data);

//textures.c
void	open_texture(t_cub *data, t_data *texture);
void	open_all_textures(t_cub *data);
int		get_texture_color(int x, int y, t_data *texture);

//doors.c
void	allocate_doors_sprites(t_cub *data);
void	move_doors_sprites(t_cub *data);
void	reset_tex_pos(t_cub *data);
void	open_door(t_cub *data);

//sprites.c
int		parse_sprites(char c, int row, int col, t_cub *data);
void	init_sprites(t_cub *data);
void	fill_sprite(t_cub *data, int row, int col);

//sounds.c
void	background_music(void);
void	door_sound(void);

//utils.c
int		str_is_digit(char *str);
void	free_str_arr(char **str);
void	ft_error(char *msg, t_cub *data);

//free.c
void	free_all_shit(t_cub *data);
void	free_all_textures(t_cub *data);
void	free_map(t_cub *data);
void	free_t_data(t_data *data, void *mlx_ptr);
void	free_doors_sprites(t_cub *data);

#endif
