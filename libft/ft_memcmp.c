/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 00:28:17 by ialinaok          #+#    #+#             */
/*   Updated: 2022/10/25 15:09:28 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* function compares n bytes (interpreted as unsigned char) of the memory areas
 * pointed to by s1 and s2 
 * returns an integer less than, equal to, or greater than zero if the first n 
 * bytes of s1 is found, respectively, to be less than, to match, or be greater 
 * than the first n bytes of s2 */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*ptr_s1 != *ptr_s2)
			return (*ptr_s1 - *ptr_s2);
		ptr_s1++;
		ptr_s2++;
		n--;
	}
	return (0);
}
