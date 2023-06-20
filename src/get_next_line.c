/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:38:12 by lechon            #+#    #+#             */
/*   Updated: 2023/06/20 09:46:00 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_freejoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*get_line(char *str, char *tmp)
{
	size_t	i;
	size_t	len;
	char	*line;

	i = 0;
	len = 0;
	if (!tmp[len])
		return (NULL);
	while (tmp[len] && tmp[len] != '\n')
		len++;
	len += (tmp[len] == '\n');
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (i < len)
		line[i++] = *tmp++;
	while (*tmp)
	{
		str[i - len] = *tmp++;
		i++;
	}
	str[i - len] = '\0';
	return (line);
}

char	*get_line_store(char *str)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	i += (str[i] == '\n');
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (j < i)
		line[j++] = *str++;
	while (*str)
	{
		*(str - i) = *str;
		str++;
	}
	*(str - i) = '\0';
	return (line);
}

char	*get_str(int fd, char *str)
{
	ssize_t	nbyte;
	char	*buf;
	char	*tmp;

	nbyte = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tmp || !buf)
		return (NULL);
	ft_memcpy(tmp, str, ft_strlen(str) + 1);
	while (nbyte > 0 && !ft_strchr(tmp, '\n'))
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte <= 0)
		{
			free(buf);
			if (tmp[0] != '\0')
				return (tmp);
			return (free(tmp), NULL);
		}
		buf[nbyte] = '\0';
		tmp = ft_freejoin(tmp, buf);
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
	if (ft_strchr(store, '\n'))
		line = get_line_store(store);
	else
	{
		tmp = get_str(fd, store);
		if (!tmp || (!tmp[0] && !store[0]))
		{
			free(tmp);
			return (NULL);
		}
		line = get_line(store, tmp);
		free(tmp);
	}
	return (line);
}
