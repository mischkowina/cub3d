/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:05:34 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 16:38:59 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <stdbool.h>
# include <sys/time.h>

# define WIDTH 			1240
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
# define KEY_SHIFT_R	258
# define KEY_SHIFT_L	257
# define MOVESPEED		0.1

# define PLAYER_SIZE	10

//@Alina: do we still need to colors?
# define BLACK			0x000000
# define WHITE			0xFFFFFF
# define GREY			0xA1A1A1
# define PINK			0x0F542D4
# define LIGHT_PINK		0xa3819c
# define BRIGHT_PINK		0xE6AEDB
# define YELLOW			0xFFDF07
# define GREEN			0x00FF00
# define ORANGE			0xFF9933
# define BLUE			0x0099FF
# define RED				0xFF0000
# define PURPLE			0x9900FF
# define BLUE_SKY		0xb3fcff
# define GREEN_GRASS		0xed2459

# define PI				3.1415926535

# define FOV_D			60
# define FOV			M_PI / 180 * FOV_D
# define ROT_ANGLE		M_PI / 36.0

//@Alina: do we use this?
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
	int		bpp;
	int		line_length;
	int		endian;
	int		color;
	int		px_x;
	int		px_y;
	char	*filename;
	int		width;
	int		height;
	double	offset;
	double	size_factor;
}				t_img;

typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct s_vec_int
{
	int			x;
	int			y;
}				t_vec_int;

typedef struct s_minimap
{
	t_vec_int	pos;
}				t_minimap;

typedef struct s_door {
	int			col;
	int			row;
	int			opening;
	int			closed;
}				t_door;

typedef struct s_obj
{
	int			col;
	int			row;
	t_img		*tex;
	double		tex_pos_x;
	int			done;
	double		dist;
	int			nbr_rays;
	int			first_ray;
	int			width;
}				t_obj;

typedef struct s_ray
{
	t_vec		dir;
	t_vec		delta_dist;
	int			map_x;
	int			map_y;
	t_vec		side_dist;
	int			step_x;
	int			step_y;
	int			ori;
	double		full_dist;
	int			x;
	int			nbr_objects;
	void		*cur_obj;
}				t_ray;

typedef struct s_data
{
	t_minimap	minimap;
	t_vec		mouse;
	double		move_speed;
	double		rotation_speed;
	double		fps;
	long long	old_time;
	long long	new_time;
	void		*mlx;
	void		*win;
	t_img		img;
	t_trgb		trgb;//@ALina: do we need this?
	t_vec		pos;
	t_vec		dir;
	t_vec		camera_plane;
	char		player_dir;
	float		p_angle;
	float		pdx;
	float		pdy;
	t_ray		*cur_ray;
	int			counter;
	t_img		n_texture;
	t_img		e_texture;
	t_img		s_texture;
	t_img		w_texture;
	t_img		d_texture;
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
	t_img		**mummy;
	int			cur_mummy;
	t_img		chest;
	t_img		tut;
	pid_t		pid_music;
	int			guns_out;
	int			guns_down;
	int			guns_shot;
	t_img		**weapons;
	int			cur_weapon;
}				t_data;

typedef struct s_delta
{
	int			dx;
	int			dy;
	double		small_ray;
}				t_delta;

	// main.c //
int			check_input(int argc, char **argv);
void		start_game(t_data *data);
int			render(t_data *data);

	// init.c //
void		init(t_data *data);
void		init_minimap(t_data *data);
void		init_orientation(t_data *data);
void		init_data(t_data *data);
void		init_parsed_values(t_data *data);

	// init_sprites.c //
void		init_sprites(t_data *data);
void		init_mummies(t_data *data);
void		init_textures(t_data *data);
void		free_texture_array(t_data *data, t_img **img);

	// parser.c //
void		parser(char *file, t_data *data);
int			parse_info_type(t_data *data, char *line);
char		*parse_texture(char *line, t_data *data);
int			parse_color(char *line, t_data *data);
int			determine_color_value(char **split, t_data *data);

	// parser_map.c //
void		parse_map(t_data *data, char *line, int fd);
void		check_prev_input(t_data *data);
void		fill_map_array(t_data *data, char *map_str);
int			copy_map_tile(char c, int row, int col, t_data *data);
void		copy_player_position(t_data *data, int col, int row, char c);

	// check_map.c //
void		allocate_map_array(t_data *data, char **map_rows);
void		check_map_array(t_data *data);
void		check_tile(t_data *data, int row, int col, int *pos);
int			check_if_accessible(t_data *data, int x, int y);
void		*check_door_ahead(t_data *data);

	// main_engine.c //
void		draw_grid(t_data *data);
void		draw_minimap(t_data *data);

	// window.c //
void		pixel_put(t_img *img, int color);
int			key_hooks(int keycode, t_data *data);
int			mouse_rotation(int x, int y, t_data *data);
int			close_x(t_data *data);

	// math.c //
void		find_vector_values(t_vec *vec, double angle);
void		normalize_vector(t_vec *vec);
void		perpendicular_vector(t_vec *vec);
void		calculate_distance(t_data *data);

	// ray_engine.c //
void		cast_rays(t_data *data, t_ray *ray, int i);
void		do_the_dda(t_data *data, t_ray *ray);
void		dda_math(t_ray *ray);
void		calculate_step(t_data *data, t_ray *ray);
void		raycasting(t_data *data);

	// ray.c //
void		ray_wall(t_data *data, t_img *texture);
void		raycasting_walls(t_data *data);
void		ray_door(t_data *data, t_door *door);
void		ray_sprite(t_data *data, t_obj *sprite);
void		draw_sprite_ray(t_data *data, t_obj *sprite, int start, int end);

	// ray_sprites.c //
int			identify_object(t_data *data, t_ray *ray);
void		do_the_dda_sprites(t_data *data, t_ray *ray);
int			check_x_position(t_data *data, t_obj *spr, t_img *tex, int width);
int			adjust_start(int start, t_img *texture, int height);
int			adjust_end(int end, t_img *texture, int height);

	// keys.c //
void		w_key_pressed(t_data *data);
void		s_key_pressed(t_data *data);
void		a_key_pressed(t_data *data);
void		d_key_pressed(t_data *data);

	// rotation.c //
void		rotate(t_data *data, double angle);
void		update_move_rot_speeds(t_data *data);
long long	time_now(void);
int			mouse_rotation(int x, int y, t_data *data);

	// minimap.c //
void		draw_point(int x, int y, t_img *img, int color);
void		draw_player(t_data *data);
void		draw_player_point(int x, int y, t_img *img, int color);
void		draw_line(t_vec_int start, t_vec_int end, t_data *data, int color);
void		render_minimap(t_data *data);

	// images.c //
void		ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void		prep_image(t_data *data);

	// textures.c //
void		open_texture(t_data *data, t_img *texture);
void		open_all_textures(t_data *data);
int			get_texture_color(t_data *data, t_img *texture, int y);
t_img		*identify_texture(t_data *data);
int			get_texture_color_sprite(t_img *texture, int x, int y);

	// doors.c //
void		allocate_doors_sprites(t_data *data);
void		move_doors_sprites(t_data *data);
void		open_door(t_data *data);
void		*check_if_door(t_data *data, int x, int y);

	// sprites.c //
int			parse_sprites(char c, int row, int col, t_data *data);
void		fill_sprite(t_data *data, int row, int col);
void		*check_if_sprite(t_data *data, int x, int y);
double		get_sprite_distance(t_data *data, t_obj	*sprite);
void		move_reset_sprites(t_data *data);

	// weapons.c //
void		init_weapons(t_data *data);
void		ray_weapons(t_data *data, int x);
void		move_weapons(t_data *data);

	// sounds.c //
void		play_sound(char *sound);
void		kill_music(void);

	// utils.c //
int			str_is_digit(char *str);
void		free_str_arr(char **str);
void		ft_error(char *msg, t_data *data);

	// free.c //
void		free_all_shit(t_data *data);
void		free_all_textures(t_data *data);
void		free_map(t_data *data);
void		free_t_img(t_img *img, void *mlx_ptr);
void		free_doors_sprites(t_data *data);

#endif
