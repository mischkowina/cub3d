/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 00:49:39 by ialinaok          #+#    #+#             */
/*   Updated: 2022/12/14 13:58:17 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* function locates the	first occurrence of the	null-terminated string needle 
 * in the string big, where not more than n characters are searched
 * characters that appear after a `\0' character are not searched */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	char	*occ;
	size_t	needle_len;
	int		i;

	i = 0;
	needle_len = ft_strlen(needle);
	occ = (char *) haystack;
	if (needle_len == 0)
		return (occ);
	if (needle_len > ft_strlen(haystack))
		return (NULL);
	while (needle_len + i <= n)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
				return (&occ[i]);
		}
		i++;
	}
	return (NULL);
}
