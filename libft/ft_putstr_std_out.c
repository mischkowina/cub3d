/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_std_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:48:12 by apielasz          #+#    #+#             */
/*   Updated: 2022/10/25 15:16:15 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_std_out(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		i = 6;
	}
	return (i);
}
