/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:52:15 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/20 17:06:09 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*trim;

	if (s1 != NULL)
	{
		while (set != NULL && *s1 != '\0' && ft_strchr(set, *s1) != NULL)
			++s1;
		len = ft_strlen(s1);
		while (set != NULL && len > 0 && ft_strchr(set, s1[len - 1]) != NULL)
			--len;
		trim = ft_strndup(s1, len);
	}
	else
		trim = NULL;
	return (trim);
}
