/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:06:31 by ialinaok          #+#    #+#             */
/*   Updated: 2022/10/25 15:57:09 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(char const *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*put;

	put = str;
	while (n > 0)
	{
		*put++ = '\0';
		n--;
	}
}

char	*ft_strchr(char const *str, int c)
{
	char	*ptr;

	ptr = (char *) str;
	while (*ptr)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	if (*ptr == c)
		return (ptr);
	return (NULL);
}
