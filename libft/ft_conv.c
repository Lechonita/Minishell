/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:50:04 by bebigel           #+#    #+#             */
/*   Updated: 2023/02/28 11:40:13 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr(uintptr_t nbp)
{
	if (!nbp)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		write(1, "0x", 2);
		ft_putnbr_basep(nbp, "0123456789abcdef");
		return (ft_countp(nbp, 16) + 2);
	}
	return (0);
}

int	ft_hexa(unsigned int nb, char c)
{
	if (c == 'x')
	{
		ft_putnbr_baseus((unsigned int)nb, "0123456789abcdef");
		return (ft_countus(nb, 16));
	}
	else if (c == 'X')
	{
		ft_putnbr_baseus((unsigned int)nb, "0123456789ABCDEF");
		return (ft_countus(nb, 16));
	}
	return (0);
}

int	ft_nbr(int nb, char c)
{
	if (c == 'd' || c == 'i')
	{
		ft_putnbr_base(nb, "0123456789");
		return (ft_count(nb, 10));
	}
	else if (c == 'u')
	{
		ft_putnbr_baseus((unsigned int)nb, "0123456789");
		return (ft_countus(nb, 10));
	}
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

// int	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }
