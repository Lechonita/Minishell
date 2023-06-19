/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:46:54 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:02:43 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_count(int nb, int base)
{
	static int	count = 0;
	long long	lnb;
	int			co;

	lnb = (long long)nb;
	co = count;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		lnb *= -1;
		count++;
	}
	if (lnb > 0)
	{
		count++;
		ft_count(lnb / base, base);
	}
	co = count - co;
	return (co);
}

int	ft_countus(unsigned int nb, int base)
{
	static int			count = 0;
	unsigned long long	lnb;
	int					co;

	lnb = (unsigned long long)nb;
	co = count;
	if (nb == 0)
		return (1);
	if (lnb > 0)
	{
		count++;
		ft_countus(lnb / base, base);
	}
	co = count - co;
	return (co);
}
