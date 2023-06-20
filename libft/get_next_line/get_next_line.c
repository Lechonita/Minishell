/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:11:58 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 09:43:14 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_free_join_gnl(char *s1, char *s2)
{
	char	*new;
	int		lens1;
	int		lens2;
	size_t	i;
	size_t	c;

	if (!s1)
	{
		s1 = malloc(sizeof(char) + 1);
		s1[0] = 0;
	}
	lens1 = ft_strlen_gnl((char *)s1);
	lens2 = ft_strlen_gnl((char *)s2);
	new = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	c = -1;
	while (s2[++c])
		new[i + c] = s2[c];
	new[i + c] = '\0';
	return (free(s1), new);
}

char	*get_line(char *store, char *tmp)
{
	char		*line;
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	if (!tmp[0])
		return (NULL);
	while (tmp[len] && tmp[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	len++;
	line[len] = '\0';
	while (i < len)
		line[i++] = *tmp++;
	while (*tmp)
		store[i++ - len] = *tmp++;
	store[i - len] = '\0';
	return (line);
}

char	*get_line_store(char *store)
{
	char		*line;
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	if (!store[0])
		return (NULL);
	while (store[len] && store[len] != '\n')
		len++;
	len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (i < len)
		line[i++] = *store++;
	while (*store)
	{
		*(store - len) = *store;
		store++;
	}
	*(store - len) = 0;
	return (line);
}

char	*get_str(int fd, char *store)
{
	char	*buf;
	char	*tmp;
	ssize_t	nbo;

	nbo = 1;
	tmp = malloc(sizeof(char) * (ft_strlen_gnl(store) + 1));
	ft_memcpy_gnl(tmp, store, ft_strlen_gnl(store) + 1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (nbo > 0)
	{
		nbo = read(fd, buf, BUFFER_SIZE);
		if (nbo < 0)
			return (free(buf), NULL);
		buf[nbo] = 0;
		tmp = ft_free_join_gnl(tmp, buf);
		if (ft_strchr_gnl(tmp, '\n'))
			break ;
	}
	return (free(buf), tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	store[BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr_gnl(store, '\n'))
		line = get_line_store(store);
	else
	{
		tmp = get_str(fd, store);
		if (!tmp || (!tmp[0] && !store[0]))
			return (free(tmp), NULL);
		line = get_line(store, tmp);
		free(tmp);
	}
	return (line);
}
