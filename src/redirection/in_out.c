/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:51:11 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/11 16:07:14 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redirection_less(t_bigshell *data, t_redir *redir)
{
	if (access(redir->file, F_OK) < 0)
	{
		msg_not_found(FILE_NOT_FOUND, redir->file);
		data->exit_status = 1;
		redir->fd = 0;
	}
	else if (access(redir->file, R_OK) < 0)
	{
		msg_not_found(PERM_DENIED, redir->file);
		data->exit_status = 127;
		redir->fd = 0;
	}
	else if (access(redir->file, F_OK & R_OK) == 0)
	{
		redir->fd = open(redir->file, O_RDONLY);
		if (redir->fd < 0)
			return (free_all(data), ft_exit(errno, strerror(errno)));
	}
}

void	redirection_great(t_bigshell *data, t_redir *redir)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) < 0)
	{
		msg_not_found(PERM_DENIED, redir->file);
		data->exit_status = 127;
		redir->fd = 0;
	}
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)));
}

void	redirection_append(t_bigshell *data, t_redir *redir)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) < 0)
	{
		msg_not_found(PERM_DENIED, redir->file);
		data->exit_status = 127;
		redir->fd = 0;
	}
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)));
}

void	open_fd(t_bigshell *data, t_redir *redir)
{
	t_redir	*el;

	el = redir;
	while (el != NULL)
	{
		if (!ft_strncmp(el->type, "<<", 2))
			redirection_here_doc(data, el);
		else if (!ft_strncmp(el->type, "<", 1))
			redirection_less(data, el);
		else if (!ft_strncmp(el->type, ">>", 2))
			redirection_append(data, el);
		else if (!ft_strncmp(el->type, ">", 1))
			redirection_great(data, el);
		el = el->next;
	}
}

void	redir_job(t_bigshell *data)
{
	data->in = init_redir(data, LESS);
	data->out = init_redir(data, GREAT);
	open_fd(data, data->in);
	open_fd(data, data->out);
	print_redir(data, "IN");
	print_redir(data, "OUT");
}

/*
void	check_access(t_redir *redir)
{
	t_redir	*el;
	t_redir	*el_perm;

	el = redir;
	el_perm = redir;
	while (el != NULL)
	{
		if (access(el->file, F_OK) == -1)
			el->access = NO_ACCESS;
		if (access(el->file, R_OK) == 0)
			el->access = RD_ACCESS;
		if (access(el->file, W_OK) == 0)
			el->access = WR_ACCESS;
		if (access(el->file, R_OK | W_OK) == 0)
			el->access = RDWR_ACCESS;
		el = el->next;
	}
	while (el_perm != NULL)
	{
		if (access(el_perm->file, X_OK) == 0 && el_perm->access > NO_ACCESS)
			el_perm->exec_perm = 1;
		el_perm = el_perm->next;
	}
}
*/