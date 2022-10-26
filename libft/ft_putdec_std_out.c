/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec_std_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:53:45 by apielasz          #+#    #+#             */
/*   Updated: 2022/10/25 15:15:15 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putdec_std_out(int n)
{
	char	intprint;
	int		ret;

	ret = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		ret++;
		if (n == -2147483648)
		{
			write(1, "2147483648", 10);
			return (ret + 10);
		}
		n *= -1;
	}
	if (n >= 10)
		ret += ft_putdec_std_out(n / 10);
	intprint = n % 10 + '0';
	write(1, &intprint, 1);
	return (1 + ret);
}
