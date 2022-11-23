#include "../cub3d.h"

/**
 * Function to allocate and initialize a struct for every door, 
 * holding a flag if the door is opening or not, the precentage
 * to which it is closed and the width of the door in pixels
 * for the current image.
 * @param data [t_data *] Pointer to struct storing the input data.
*/
void	allocate_doors(t_cub *data)
{
	int	i;

	i = 0;
	data->doors = ft_calloc(sizeof(t_door *), data->nbr_doors);
	while (i < data->nbr_doors)
	{	
		data->doors[i] = ft_calloc(sizeof(t_door), 1);
		data->doors[i]->closed = 100;
		data->doors[i]->opening = 0;
		data->doors[i++]->cur_width = 0;
	}
}

/**
 * Function to draw a ray containing a door instead of a wall. Identifies
 * the height of the wall using the distance of the ray, just as the
 * draw_wall function. Then adjusts the starting position in case the door
 * is opened to a certain degree. Lastly, iterates through every pixel
 * of the ray and identifies the respective color from the door texture.
 * @param data [t_cub *] Pointer to struct storing all the input data.
 * @param door [t_door *] Pointer to the struct storing the information
 * about the respective door.
 * @param tex_pos [double] Contains the respective x-coordinate for the texture.
*/
void	ray_door(t_cub *data, t_door *door, double tex_pos_x)
{
	int		start;
	int		end;
	double	tex_pos_y;
	double	step;
	int		col;

	start = - (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	end = (HEIGHT / data->cur_ray->dist) / 2 + HEIGHT / 2.0;
	start += (end - start) * (100 - door->closed) / 100;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	tex_pos_y = 0;
	step = 1.0 * data->D_texture.height / (HEIGHT / data->cur_ray->dist);
	while (start < end)
	{
		col = get_texture_color(tex_pos_x, tex_pos_y, &(data->D_texture));
		ft_mlx_pixel_put(&(data->img), data->cur_ray->x, start, col);
		tex_pos_y += step;
		start++;
	}
}

void	draw_doors(t_cub *data)
{
	double	tex_pos_x;
	int		i;//to be deleted
	
	i = WIDTH / 8;//to be deleted
	data->cur_ray->x = 0;
	tex_pos_x = 0;
	data->cur_ray->dist = 2;//instead has to be determined by raycaster
	data->doors[0]->cur_width = 400;//for testing, has to be identified in first iteration
	while (data->cur_ray->x < WIDTH)//ALINA: second iteration: give distance to doors, ignore rays that hit walls
	{
		//function to recalculate ray
		if (data->cur_ray->x == (WIDTH / 2 - i))//instead: identify whether hits a door, and if yes, at which distance and which door -> maybe struct for the ray?
		{
			while (tex_pos_x < data->D_texture.width && data->cur_ray->x < WIDTH)
			{
				ray_door(data, data->doors[0], tex_pos_x);
				tex_pos_x += 1.0 * data->D_texture.width / data->doors[0]->cur_width;
				data->cur_ray->x++;
				//function to recalculate ray
			}
		}
		data->cur_ray->x++;
	}
}

/**
 * Function to interact with a door. First checks if there is a door in the
 * proximity / FOV (???) to interact with. If so, changes the opening flag of
 * the door, depending on whether it was currently closing or opening.
 * @param [t_cub *] Pointer to struct storing all the input data.
*/
void	open_door(t_cub *data)
{
	int	idx;

	//check if conditions are met: adjacent to the door and door within FOV?
	//identify which door!
	idx = 0;//to be replaced
	if (data->doors[idx]->opening == 0)
		data->doors[idx]->opening = 1;
	else
		data->doors[idx]->opening = 0;
}
