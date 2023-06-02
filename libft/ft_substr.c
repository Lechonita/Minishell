/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:19:35 by bebigel           #+#    #+#             */
/*   Updated: 2023/01/02 15:17:55 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if ((int)start > ft_strlen((char *)s))
		return (ft_strdup(""));
	else
	{
		if (len > (size_t)ft_strlen((char *)(s + start)))
			len = ft_strlen((char *)(s + start));
		new = (char *)malloc(sizeof(char) * (len + 1));
		if (!new)
			return (NULL);
		while (s[start + i] && i < len)
		{
			new[i] = s[i + start];
			i++;
		}
	}
	new[i] = '\0';
	return (new);
}
