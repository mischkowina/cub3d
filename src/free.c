
#include "../cub3d.h"

void	free_all_shit(t_cub *data)
{
    free_wall_textures(data);//(t_data)
    free_map(data);
    //doors
    //sprites
    //ray
    //mummy (t_data)
    //chest (t_data)
    //tut   (t_data)
    free(data->img.addr);
    mlx_destroy_image(data->mlx_ptr, data->img.img);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    free(data->mlx_ptr);
}

void    free_wall_textures(t_cub *data)
{
    if (data->N_texture.filename)
        free(data->N_texture.filename);
    if (data->N_texture.addr)
        free(data->N_texture.addr);
    if (data->N_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->N_texture.img);
    if (data->E_texture.filename)
        free(data->E_texture.filename);
    if (data->E_texture.addr)
        free(data->E_texture.addr);
    if (data->E_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->E_texture.img);
    if (data->S_texture.filename)
        free(data->S_texture.filename);
    if (data->S_texture.addr)
        free(data->S_texture.addr);
    if (data->S_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->S_texture.img);
    if (data->W_texture.filename)
        free(data->W_texture.filename);
    if (data->W_texture.addr)
        free(data->W_texture.addr);
    if (data->W_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->W_texture.img);
}

void    free_map(t_cub *data)
{
    int i;

    i = 0;
    while (data->map[i])
        free(data->map[i++]);
    free(data->map);
}
