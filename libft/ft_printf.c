/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:46:54 by bebigel           #+#    #+#             */
/*   Updated: 2022/12/27 09:17:01 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conv(va_list args, char c)
{
	if (c == 'd' || c == 'i' || c == 'u')
		return (ft_nbr((unsigned int)va_arg(args, int), c));
	else if (c == 'x' || c == 'X')
		return (ft_hexa((unsigned int)va_arg(args, unsigned int), c));
	else if (c == 'p')
		return (ft_ptr(va_arg(args, uintptr_t)));
	else if (c == 'c')
		return (ft_countchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_countstr(va_arg(args, char *)));
	else if (c == '%')
	{
		write(1, &c, 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		i;
	int		co;

	if (!fmt)
		return (-1);
	i = 0;
	co = 0;
	va_start(args, fmt);
	while (fmt[i] && i < ft_strlen(fmt))
	{
		if (fmt[i] == '%')
		{
			co += ft_conv(args, fmt[i + 1]);
			i++;
		}
		else
			co += ft_countchar(fmt[i]);
		i++;
	}
	va_end(args);
	return (co);
}
