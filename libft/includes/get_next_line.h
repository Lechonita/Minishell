/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:07:41 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 17:08:41 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>	//read
# include <fcntl.h>		//open
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# if BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

	/*	GNL fonctions	*/
char	*get_str(int fd, char *store);
char	*get_next_line(int fd);
char	*get_line(char *store, char *tmp);
char	*get_line_store(char *store);

	/*	annexes	*/
// char	*ft_strjoin_gnl(char const *s1, char const *s2);
void	*ft_memcpy_gnl(void *dest, const void *src, size_t n);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*ft_free_join_gnl(char *c, char *buf);
char	*ft_strchr_gnl(const char *s, int c);
int		ft_strlen_gnl(const char *s);

#endif