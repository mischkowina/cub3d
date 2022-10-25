/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_std_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:35:45 by apielasz          #+#    #+#             */
/*   Updated: 2022/10/25 15:16:26 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putuint_std_out(unsigned int uint)
{
	char	uintprint;
	int		ret;

	ret = 0;
	if (uint >= 10)
		ret += ft_putuint_std_out(uint / 10);
	uintprint = uint % 10 + '0';
	write(1, &uintprint, 1);
	return (1 + ret);
}
