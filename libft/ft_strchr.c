/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:24:47 by ialinaok          #+#    #+#             */
/*   Updated: 2022/12/14 13:59:40 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* function returns a pointer to the first occurrence of the character c 
 * in the string */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;

	ptr = (char *)str;
	while (*ptr != '\0')
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	if (*ptr == c)
		return (ptr);
	return (NULL);
}
