/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:27 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 09:42:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	char	*new;

	if (!s || !f)
		return (NULL);
	size = ft_strlen((char *)s);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = '\0';
	while (size-- > 0)
		new[size] = (*f)(size, s[size]);
	return (new);
}
