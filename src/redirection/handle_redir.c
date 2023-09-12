/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:17:42 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/12 11:43:54 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	read_stdin_hd(t_redir *redir)
{
	char	*tmp;

	set_signal_here_doc();
	while (1)
	{
		dprintf(2, "\033[1;31mexit satus [%d]\033[0m\n", g_global.exit_status);
		if (g_global.exit_status == 130)
			return ;
		tmp = readline("> ");
		if (tmp == NULL)
			return (ctrl_d_here_doc(tmp, redir->file));
		if (ft_strlen(tmp) == ft_strlen(redir->file)
			&& ft_strncmp(tmp, redir->file, ft_strlen(redir->file)) == 0)
			return (free(tmp));
		ft_putendl_fd(tmp, redir->fd);
		free(tmp);
	}
}

int	redirection_here_doc(t_redir *redir)
{
	redir->fd = open("minishell_here_doc", O_CREAT | O_WRONLY, 0644);
	if (redir->fd < 0)
		return (ft_error(errno, strerror(errno)), errno);
	read_stdin_hd(redir);
	dprintf(2, "\033[1;32mexit satus [%d]\033[0m\n", g_global.exit_status);
	close(redir->fd);
	redir->fd = open("minishell_here_doc", O_RDONLY);
	if (redir->fd < 0)
		return (ft_error(errno, strerror(errno)), errno);
	g_global.heredoc = 1;
	return (1);
}

int	redirection_less(t_redir *redir)
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
			return (ft_error(errno, strerror(errno)), errno);
	}
	return (1);
}

int	redirection_great(t_redir *redir)
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
		return (ft_error(errno, strerror(errno)), errno);
	return (1);
}

int	redirection_append(t_redir *redir)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) < 0)
	{
		msg_not_found(PERM_DENIED, redir->file);
		g_global.exit_status = 1;
		redir->fd = 0;
		return (0);
	}
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
		return (ft_error(errno, strerror(errno)), errno);
	return (1);
}
