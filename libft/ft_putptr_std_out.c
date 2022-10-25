/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_std_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:09:58 by apielasz          #+#    #+#             */
/*   Updated: 2022/10/25 15:16:01 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex_part(unsigned long long ptr);

int	ft_putptr_std_out(void *ptr)
{
	int		ret;

	ret = 0;
	if (!ptr)
		ret = ft_putstr_std_out("0x0");
	else
	{
		ret = ft_putstr_std_out("0x");
		ret += ft_puthex_part((unsigned long long) ptr);
	}
	return (ret);
}

static int	ft_puthex_part(unsigned long long ptr)
{
	char	ptrprint;
	int		ret;
	
	ret = 0;
	if (ptr >= 0x10)
		ret += ft_puthex_part(ptr / 16);
	ptrprint = ptr % 16;
	if (ptrprint <= 9)
		ptrprint += '0';
	else
		ptrprint += 87;
	write(1, &ptrprint, 1);
	return (1 + ret);
}
