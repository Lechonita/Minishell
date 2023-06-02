/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:17:21 by bebigel           #+#    #+#             */
/*   Updated: 2022/11/18 14:08:02 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sun;
	unsigned char	*sdeux;

	sun = (unsigned char *)s1;
	sdeux = (unsigned char *)s2;
	while (n--)
	{
		if (*sun > *sdeux)
			return (1);
		else if (*sun < *sdeux)
			return (-1);
		sun++;
		sdeux++;
	}
	return (0);
}
