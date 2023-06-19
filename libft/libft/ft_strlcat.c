/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:14 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:12:14 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	ld;
	size_t	ls;

	i = 0;
	if ((!dest || !src) && !size)
		return (0);
	ld = ft_strlen(dest);
	ls = ft_strlen((char *)src);
	if (size == 0 || size <= ld)
		return (ls + size);
	while (src[i] && i + ld < size - 1)
	{
		dest[i + ld] = (char)src[i];
		i++;
	}
	dest[i + ld] = '\0';
	return (ld + ls);
}
