/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:52:27 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 09:42:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t		i;
	char		*copy;

	i = 0;
	copy = malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	while (i < n && src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
