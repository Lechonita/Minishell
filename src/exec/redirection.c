/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:03:19 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/06 17:32:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

/* < */
static void	redirection_left(t_bigshell *bs)
{
	char	*file;

	file = bs->exec->in_file;
	if (access(file, F_OK) < 0)
	{
		msg_not_found(FILE_NOT_FOUND, file);
		bs->exec->fd_in = 0;
		return ;
	}
	else if (access(file, R_OK) < 0)
	{
		msg_not_found(PERM_DENIED, file);
		bs->exec->fd_in = 0;
		return ;
	}
	else if (access(file, F_OK & R_OK) == 0)
	{
		bs->exec->fd_in = open(file, O_RDONLY);
		if (bs->exec->fd_in < 0)
			return (free_all(bs), ft_exit(errno, strerror(errno)));
	}
	return ;
}

/* > */
static void	redirection_right(t_bigshell *bs)
{
	char	*file;

	file = bs->exec->out_file;
	if (access(file, F_OK) == 0 && access(file, W_OK) < 0)
	{
		msg_not_found(PERM_DENIED, file);
		bs->exec->fd_out = 0;
		return ;
	}
	bs->exec->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (bs->exec->fd_out < 0)
		return (free_all(bs), ft_exit(errno, strerror(errno)));
	return ;
}

/* >> */
static void	redirection_append(t_bigshell *data)
{
	char	*file;

	file = data->exec->out_file;
	if (access(file, F_OK) == 0 && access(file, W_OK) < 0)
	{
		msg_not_found(PERM_DENIED, file);
		data->exec->fd_out = 0;
		return ;
	}
	data->exec->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->exec->fd_out < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)));
	return ;
}

void	redir_in_file(t_bigshell *data)
{
	t_token	*tok;

	if (data->exec->in_file == NULL)
	{
		data->exec->fd_in = 0;
		data->exec->no_redir = 1;
		return ;
	}
	tok = data->token;
	while (tok != NULL)
	{
		if (ft_strncmp(tok->value, "<<", 2) == 0)
		{
			handle_here_doc(data, data->exec->in_file);
			break ;
		}
		else if (ft_strncmp(tok->value, "<", 1) == 0)
		{
			redirection_left(data);
			break ;
		}
		tok = tok->next;
	}
	return ;
}

void	redir_out_file(t_bigshell *data)
{
	t_token	*tok;

	if (data->exec->out_file == NULL)
	{
		data->exec->fd_out = 0;
		data->exec->no_redir = 2 + data->exec->no_redir;
		return ;
	}
	tok = data->token;
	while (tok != NULL)
	{
		if (ft_strncmp(tok->value, ">>", 2) == 0)
		{
			redirection_append(data);
			break ;
		}
		else if (ft_strncmp(tok->value, ">", 1) == 0)
		{
			redirection_right(data);
			break ;
		}
		tok = tok->next;
	}
	return ;
}