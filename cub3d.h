
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "/usr/X11/include/X11/X.h"
# include <math.h>
# include "libft/libft.h"

# define WIDTH 			1440
# define HEIGHT			1080

# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
//add W, A, S, D

typedef	struct s_data
{
	char	*N_texture;
	char	*E_texture;
	char	*S_texture;
	char	*W_texture;
	int		col_ceiling;
	int		col_floor;
	int		**map;
	int		width_map;
	int		height_map;
	char	player_dir;
}				t_data;

int		check_input(int argc, char **argv);
int		init_data(t_data *data);
void	ft_error(char *msg);
int		parser(char *file, t_data *data);
char	*parse_texture(char *line);
int		parse_color(char *line);
int		determine_color_value(char **split);
int		str_is_digit(char *str);
int		parse_map(t_data *data, char *line, int fd);
int		check_prev_input(t_data *data);
int		fill_map_array(t_data *data, char *map_str);
int		check_map_array(t_data *data);
void	free_str_arr(char **str);

#endif
