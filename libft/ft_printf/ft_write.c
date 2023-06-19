/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:50:04 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:03:29 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_putnbr_base(int nbr, char *base)
{
	long long	lnb;

	lnb = (long long)nbr;
	if (nbr < 0)
	{
		ft_putchar('-');
		lnb = -lnb;
	}
	if (lnb / ft_strlen(base))
		ft_putnbr_base(lnb / ft_strlen(base), base);
	ft_putchar(base[lnb % ft_strlen(base)]);
}

void	ft_putnbr_baseus(unsigned int nbr, char *base)
{
	unsigned long	lnb;

	lnb = (unsigned long)nbr;
	if (nbr == 0)
	{
		ft_putchar(base[0]);
		return ;
	}
	if (lnb / ft_strlen(base))
		ft_putnbr_baseus(lnb / ft_strlen(base), base);
	ft_putchar(base[lnb % ft_strlen(base)]);
}

void	ft_putnbr_basep(uintptr_t nbr, char *base)
{
	unsigned long long	lnb;

	lnb = (unsigned long long)nbr;
	if (nbr == 0)
	{
		ft_putchar(base[0]);
		return ;
	}
	if (lnb / ft_strlen(base))
		ft_putnbr_basep(lnb / ft_strlen(base), base);
	ft_putchar(base[lnb % ft_strlen(base)]);
}
