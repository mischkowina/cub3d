/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:50:22 by apielasz          #+#    #+#             */
/*   Updated: 2022/10/25 15:14:44 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	put_format(const char **format, va_list *arg_list);

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	int		ret_count;

	ret_count = 0;
	va_start(arg_list, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret_count += put_format(&format, &arg_list);
		}
		else
		{
			write(1, format, 1);
			ret_count += 1;
		}
		format++;
	}
	va_end(arg_list);
	return (ret_count);
}

static int	put_format(const char **format, va_list *arg_list)
{
	int	ret_count;

	ret_count = 0;
	if (**format == 'c')
		ret_count = ft_putchar_std_out(va_arg(*arg_list, int));
	else if (**format == 's')
		ret_count = ft_putstr_std_out(va_arg(*arg_list, char *));
	else if (**format == 'p')
		ret_count = ft_putptr_std_out((void *) va_arg(*arg_list, void *));
	else if (**format == 'd' || **format == 'i')
		ret_count = ft_putdec_std_out(va_arg(*arg_list, int));
	else if (**format == 'u')
		ret_count = ft_putuint_std_out(va_arg(*arg_list, unsigned int));
	else if (**format == 'x')
		ret_count = ft_puthex_lower_std_out(va_arg(*arg_list, unsigned int));
	else if (**format == 'X')
		ret_count = ft_puthex_upper_std_out(va_arg(*arg_list, unsigned int));
	else if (**format == '%')
		ret_count = ft_putchar_std_out('%');
	return (ret_count);
}
