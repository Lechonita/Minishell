/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countbis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:46:54 by bebigel           #+#    #+#             */
/*   Updated: 2022/12/27 09:17:18 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countp(uintptr_t nb, int base)
{
	static int			count = 0;
	unsigned long long	lnb;
	int					co;

	lnb = (unsigned long long)nb;
	co = count;
	if (nb == 0)
		return (count);
	if (lnb > 0)
	{
		count++;
		ft_countp(lnb / base, base);
	}
	co = count - co;
	return (co);
}

int	ft_countchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_countstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}
