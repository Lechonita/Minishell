/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:45:04 by bebigel           #+#    #+#             */
/*   Updated: 2023/04/14 21:01:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	const size_t	size = ft_strlen(s) + 1;
	char			*dup;

	dup = (char *)malloc(size);
	if (dup != NULL)
		ft_strlcpy(dup, s, size);
	return (dup);
}
