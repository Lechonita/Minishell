/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:47:44 by bebigel           #+#    #+#             */
/*   Updated: 2022/11/24 16:25:34 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*p;
	int		lens1;
	int		lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen((char *)s1);
	lens2 = ft_strlen((char *)s2);
	new = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!new)
		return (NULL);
	p = new;
	while (*s1 && lens1-- > 0)
		*p++ = *(char *)s1++;
	while (*s2 && lens2-- > 0)
		*p++ = *(char *)s2++;
	*p = '\0';
	return (new);
}
