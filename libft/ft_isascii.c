/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:06:10 by ialinaok          #+#    #+#             */
/*   Updated: 2022/10/25 15:08:49 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* function checks whether c is a 7-bit unsigned int char that fits into ASCII
 * character set */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	if (ft_isascii(678) == 0)
// 	{
// 		printf("This is not found in ASCII \n");
// 	}
// 	else
// 	{
// 		printf("This is found in ASCII \n");
// 	}
// 	return (0);
// }
