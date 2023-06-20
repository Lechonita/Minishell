/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:52:15 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 09:42:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	is_in_set(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

size_t	start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1 && is_in_set(s1[start], set))
		start++;
	return (start);
}

size_t	end(char const *s1, char const *set)
{
	size_t	end;

	end = (size_t)ft_strlen((char *)s1);
	while (s1 && is_in_set(s1[end - 1], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	s;
	size_t	e;

	if (!s1 || !set)
		return (NULL);
	s = start((char *)s1, (char *)set);
	e = end((char *)s1, (char *)set);
	if (s == (size_t)ft_strlen((char *)s1))
	{
		new = malloc(sizeof(char) * 1);
		if (!new)
			return (NULL);
		new[0] = 0;
	}
	else
		new = ft_substr((char *)s1, s, e - s);
	return (new);
}
