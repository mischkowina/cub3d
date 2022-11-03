/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:03:16 by smischni          #+#    #+#             */
/*   Updated: 2022/01/10 14:01:04 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
Allocates and returns a substring from s, that begins at index start and 
is of max. size len.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (i >= len)
		str = ft_calloc((len + 1), sizeof(*s));
	else
		str = ft_calloc((i + 1), sizeof(*s));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (*(s + i) != '\0')
	{
		if (i >= start && j < len)
		{
			*(str + j) = *(s + i);
			j++;
		}
		i++;
	}
	return (str);
}
