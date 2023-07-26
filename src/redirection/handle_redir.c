/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:17:42 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/26 17:09:29 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	read_stdin_hd(t_redir *redir)
{
	int		count;
	char	*tmp;

	count = 0;
	while (1)
	{
		// set_signal_here_doc();
		tmp = readline("> ");
		if (tmp == NULL)
		{
			ctrl_d_here_doc(tmp, redir->file, count);
			break ;
		}
		if (ft_strlen(tmp) == ft_strlen(redir->file)
			&& ft_strncmp(tmp, redir->file, ft_strlen(redir->file)) == 0)
			break ;
		// add_history(tmp);
		tmp = free_strjoin(tmp, "\n");
		ft_putstr_fd(tmp, redir->fd);
		free(tmp);
		count++;
	}
	free(tmp);
	return ;
}

void	redirection_here_doc(t_bigshell *data, t_redir *redir)
{
	redir->fd = open("minishell_here_doc", O_CREAT | O_WRONLY, 0644);
	if (redir->fd < 0)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_HD_OPEN));
	read_stdin_hd(redir);
	close(redir->fd);
	redir->fd = open("minishell_here_doc", O_RDONLY);
	if (redir->fd < 0)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_HD_OPEN));
}

int	redirection_less(t_bigshell *data, t_redir *redir)
{
	if (access(redir->file, F_OK) < 0)
	{
		msg_not_found(FILE_NOT_FOUND, redir->file);
		g_global.exit_status = 1;
		redir->fd = 0;
		return (0);
	}
	else if (access(redir->file, R_OK) < 0)
	{
		msg_not_found(PERM_DENIED, redir->file);
		g_global.exit_status = 1;
		redir->fd = 0;
		return (0);
	}
	else if (access(redir->file, F_OK & R_OK) == 0)
	{
		redir->fd = open(redir->file, O_RDONLY);
		if (redir->fd < 0)
			return (free_all(data), ft_exit(errno, strerror(errno)), errno);
	}
	return (1);
}

int	redirection_great(t_bigshell *data, t_redir *redir)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) < 0)
	{
		msg_not_found(PERM_DENIED, redir->file);
		g_global.exit_status = 1;
		redir->fd = 0;
		return (0);
	}
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)), errno);
	return (1);
}

void	redirection_append(t_bigshell *data, t_redir *redir)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) < 0)
	{
		msg_not_found(PERM_DENIED, redir->file);
		g_global.exit_status = 1;
		redir->fd = 0;
	}
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)));
}
