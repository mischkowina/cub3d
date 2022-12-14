/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:39:15 by ialinaok          #+#    #+#             */
/*   Updated: 2022/12/14 14:02:50 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* function copies n bytes from memory area src to memory area dest
 * the memory areas must not overlap */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*put_dest;
	const char		*put_src;

	put_dest = dest;
	put_src = src;
	while (n > 0 && (dest != NULL || src != NULL))
	{
		*put_dest++ = *put_src++;
		n--;
	}
	return (dest);
}
