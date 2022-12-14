/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:14:46 by ialinaok          #+#    #+#             */
/*   Updated: 2022/12/14 13:59:50 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* applies the function f to each character of the string passed as argument
 * and passing its index as first argument; each character is passed by
 * address to f to be modified if necessary */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
	}
}
