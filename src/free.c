
#include "../cub3d.h"

void	free_all_shit(t_cub *data)
{
	printf("TEST\n");
	free_all_textures(data);
	printf("TEST1\n");
	free_map(data);
	printf("TEST2\n");
	if (data->cur_ray)
		free(data->cur_ray);
	printf("TEST3\n");
	free_doors_sprites(data);
	printf("TEST4\n");
	if (data->img.addr)
		free(data->img.addr);
	printf("TEST5\n");
	if (data->img.img)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	printf("TEST6\n");
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->win_ptr);//necessary?
	}
	printf("TEST6\n");
	if (data->mlx_ptr)
		free(data->mlx_ptr);
}

void	free_all_textures(t_cub *data)
{
	int	i;

	i = 0;
	free_t_data(&(data->N_texture), data->mlx_ptr);
	free_t_data(&(data->E_texture), data->mlx_ptr);
	free_t_data(&(data->S_texture), data->mlx_ptr);
	free_t_data(&(data->W_texture), data->mlx_ptr);
	free_t_data(&(data->D_texture), data->mlx_ptr);
	if (data->mummy)
	{
		while (i < 4)
		{
			if (data->mummy[i])
				free_t_data(data->mummy[i], data->mlx_ptr);
			i++;
		}
		free(data->mummy);
	}
	free_t_data(&(data->chest), data->mlx_ptr);
	free_t_data(&(data->tut), data->mlx_ptr);
}

void	free_map(t_cub *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
}

void	free_t_data(t_data *data, void *mlx_ptr)
{
	printf("TEST FREEING1\n");
	if (data->filename)
		free(data->filename);
	printf("TEST FREEING2\n");
	if (data->addr)
		free(data->addr);
	printf("TEST FREEING3\n");
	if (data->img)
		mlx_destroy_image(mlx_ptr, data->img);
	printf("TEST FREEING4\n");
	free(data->img);//necessary?
}

void	free_doors_sprites(t_cub *data)
{
	int	i;

	i = 0;
	if (data->doors)
	{
		while (i < data->nbr_doors && data->doors[i])
			free(data->doors[i++]);
		free(data->doors);
	}
	i = 0;
	if (data->sprites)
	{
		while (i < data->nbr_sprites && data->sprites[i])
			free(data->sprites[i++]);
		free(data->sprites);
	}
}
