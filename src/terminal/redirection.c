/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:03:19 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/26 12:42:01 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_access_in(t_bigshell *data, char *file)
{
	if (access(file, F_OK & R_OK) == 0)
		return (1);
	else if (access(file, F_OK) < 0)
	{
		msg_not_found(FILE_NOT_FOUND, file);
		data->exec->fd_in = 0;
		return (0);
	}
	else if (access(file, R_OK) < 0)
	{
		msg_not_found(PERM_DENIED, file);
		data->exec->fd_in = 0;
		return (0);
	}
}

/* < should redirect input */
void	redirection_left(t_bigshell *bs)
{
	int		ret;
	char	*file;

	file = bs->exec->in_file;
	if (check_access_in(bs, file))
	{
		bs->exec->fd_in = open(file, O_RDONLY);
		if (bs->exec->fd_in < 0)
			return (ft_free_all(bs), ft_exit(errno, strerror(errno)), errno);
		ret = dup2(bs->exec->fd_in, STDIN_FILENO);
		if (ret == -1)
			return (ft_free_all(bs), ft_exit(errno, strerror(errno)), errno);
		close(bs->exec->fd_in);
	}
	return ;
}

/* > should redirect output */
void	redirection_right(t_bigshell *bs)
{
	int		ret;
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
		return (free_all(bs), ft_exit(errno, strerror(errno)), errno);
	ret = dup2(bs->exec->fd_out, STDOUT_FILENO);
	if (ret == -1)
		return (free_all(bs), ft_exit(errno, strerror(errno)), errno);
	close(bs->exec->fd_out);
	return (0);
}

/* >> */
void	redirection_append(t_bigshell *data)
{
	int		ret;
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
		return (free_all(data), ft_exit(errno, strerror(errno)), errno);
	ret = dup2(data->exec->fd_out, STDOUT_FILENO);
	if (ret == -1)
		return (free_all(data), ft_exit(errno, strerror(errno)), errno);
	close(data->exec->fd_out);
	return (0);
}

void	redirection(t_bigshell *data)
{
	if (data->token->value == ">")
		redirection_right(data);
	else if (data->token->value == "<<")
		hanlde_here_doc(data);
	else if (data->token->value == "<")
		redirection_left(data);
	else if (data->token->value == ">>")
		redirection_append(data);
	return ;
}
