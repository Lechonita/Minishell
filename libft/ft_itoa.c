/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:18:45 by bebigel           #+#    #+#             */
/*   Updated: 2023/01/10 10:20:05 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		n *= -1;
		size = 1;
	}
	if (n == 0)
		size = 1;
	else
	{
		while (n)
		{
			n /= 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int			size;
	long		nbr;
	int			sign;
	char		*str;

	sign = 0;
	size = count(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	nbr = (long)n;
	if (nbr < 0)
	{
		nbr *= -1;
		str[0] = '-';
		sign = 1;
	}
	str[size] = '\0';
	while (size > sign)
	{
		str[size - 1] = nbr % 10 + '0';
		nbr /= 10;
		size --;
	}
	return (str);
}
