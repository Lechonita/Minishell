/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:17:42 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/04 10:57:39 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

// static void	gnl(t_bigshell *data, char *limiter)
// {
// 	int		len;
// 	char	*str;

// 	len = ft_strlen(limiter);
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		str = get_next_line(0);
// 		if (ft_strlen(str) == (len + 1) && ft_strncmp(str, limiter, len) == 0)
// 			break ;
// 		ft_putstr_fd(str, data->exec->fd_in);
// 		free(str);
// 	}
// 	free(str);
// 	return ;
// }

// /* << */
// void	handle_here_doc(t_bigshell *data, char *limiter)
// {
// 	int		ret;
// 	char	*file;

// 	file = data->exec->in_file;
// 	data->exec->fd_in = open(file, O_CREAT | O_WRONLY, 0644);
// 	if (data->exec->fd_in < 0)
// 		return (free_all(data), ft_exit(EXIT_FAILURE, W_HD_OPEN));
// 	gnl(data, limiter);
// 	close(data->exec->fd_in);
// 	data->exec->fd_in = open(file, O_RDONLY);
// 	if (data->exec->fd_in < 0)
// 		return (free_all(data), ft_exit(EXIT_FAILURE, W_HD_OPEN));
// 	ret = dup2(data->exec->fd_in, STDIN_FILENO);
// 	if (ret == -1)
// 		return (free_all(data), ft_exit(errno, strerror(errno)));
// 	close(data->exec->fd_in);
// }
