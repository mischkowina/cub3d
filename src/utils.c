#include "../cub3d.h"

/**
 * Function to determine whether a string contains only of digits.
 * @param str [char *] String to be checked.
 * @return [int] 1 if the string only consists of digits, else 0.
*/
int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Function to free all strings within a string array and then the string 
 * array itself.
 * @param str [char **] String array to be freed.
*/
void	free_str_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_all_shit(t_cub *data)
{
	free(data->N_texture.filename);
	free(data->N_texture.addr);
	mlx_destroy_image(data->mlx_ptr, data->N_texture.img);
	free(data->E_texture.filename);
	free(data->E_texture.addr);
	mlx_destroy_image(data->mlx_ptr, data->E_texture.img);
	free(data->S_texture.filename);
	free(data->S_texture.addr);
	mlx_destroy_image(data->mlx_ptr, data->S_texture.img);
	free(data->W_texture.filename);
	free(data->W_texture.addr);
	mlx_destroy_image(data->mlx_ptr, data->W_texture.img);
	//TBC
}

/**
 * Function to write "Error\n" to STDERR followed by a more detailed error
 * message. Message is either handed over as parameter or retrieved by calling
 * perror.
 * @param msg [char *] Customized error message to be displayed.
*/
void	ft_error(char *msg)
{
	if (msg)
		printf("Error\n%s\n", msg);
	else
		perror("Error");
	//OPEN: anything to be done before exit (mlx_destroy window, ...)?
	exit(0);//OPEN: any reason for another exit code?
}
