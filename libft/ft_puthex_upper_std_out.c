/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_upper_std_out.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:51:36 by apielasz          #+#    #+#             */
/*   Updated: 2022/10/25 15:15:44 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_upper_std_out(unsigned int hex)
{
	char	hexprint;
	int		ret;

	ret = 0;
	if (hex >= 0x10)
		ret += ft_puthex_upper_std_out(hex / 16);
	hexprint = hex % 16;
	if (hexprint <= 9)
		hexprint += '0';
	else
		hexprint += 55;
	write(1, &hexprint, 1);
	return (1 + ret);
}
