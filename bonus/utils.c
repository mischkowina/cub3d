/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:45:57 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 14:35:27 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * Function to write "Error\n" to STDERR followed by a more detailed error
 * message. Message is either handed over as parameter or retrieved by calling
 * perror.
 * @param msg [char *] Customized error message to be displayed.
*/
void	ft_error(char *msg, t_data *data)
{
	if (msg)
		printf("Error\n%s\n", msg);
	else
		perror("Error");
	if (data)
		free_all_shit(data);
	exit(0);
}
