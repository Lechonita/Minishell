/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:36:39 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 09:43:09 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s != (unsigned char )c && *s)
		s++;
	if (*s == (unsigned char )c)
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}

// char	*ft_strjoin_gnl(char const *s1, char const *s2)
// {
// 	char	*new;
// 	char	*p;
// 	int		lens1;
// 	int		lens2;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	lens1 = ft_strlen_gnl((char *)s1);
// 	lens2 = ft_strlen_gnl((char *)s2);
// 	new = malloc(sizeof(char) * (lens1 + lens2 + 1));
// 	if (!new)
// 		return (NULL);
// 	p = new;
// 	while (*s1 && lens1-- > 0)
// 		*p++ = *(char *)s1++;
// 	while (*s2 && lens2-- > 0)
// 		*p++ = *(char *)s2++;
// 	*p = '\0';
// 	return (new);
// }

// char	*ft_free_join_gnl(char *c, char *buf)
// {
// 	char	*tmp;

// 	tmp = ft_strjoin_gnl(c, buf);
// 	return (free(c), tmp);
// }

int	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	n;

	n = nmemb * size;
	if (nmemb != 0 && size > ((SIZE_MAX) - 1) / nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (n--)
		((unsigned char *)ptr)[n] = '\0';
	return (ptr);
}
