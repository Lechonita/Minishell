/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:13:16 by bebigel           #+#    #+#             */
/*   Updated: 2022/11/18 14:08:11 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	if (src == dest)
		return (dest);
	if (src < dest)
		while (n--)
			*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
