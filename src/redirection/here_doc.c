/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:17:42 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/13 16:25:48 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

/* ******************************** no list ********************************* */

static void	gnl(t_bigshell *data, char *limiter)
{
	int		len;
	char	*str;
	char	*tmp;

	len = ft_strlen(limiter);
	dprintf(2, "gnl, limiter = %s\n", limiter);
	while (1)
	{
		tmp = readline("> ");
		if (ft_strlen(tmp) == len && ft_strncmp(tmp, limiter, len) == 0)
			break ;
		str = ft_strjoin(tmp, "\n");
		ft_putstr_fd(str, data->exec->fd_in);
		free(tmp);
		free(str);
	}
	free(tmp);
	return ;
}

/* << */
void	handle_here_doc(t_bigshell *data, char *limiter)
{
	data->exec->fd_in = open("minishell_here_doc", O_CREAT | O_WRONLY, 0644);
	if (data->exec->fd_in < 0)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_HD_OPEN));
	gnl(data, limiter);
	close(data->exec->fd_in);
	data->exec->fd_in = open("minishell_here_doc", O_RDWR);
	if (data->exec->fd_in < 0)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_HD_OPEN));
}

/* ******************************* redir list ******************************* */

static void	read_stdin_hd(t_redir *redir)
{
	int		len;
	char	*str;
	char	*tmp;

	len = ft_strlen(redir->file);
	dprintf(2, "read_stdin_hd limiter = %s\n", redir->file);
	while (1)
	{
		tmp = readline("> ");
		if (ft_strlen(tmp) == len && ft_strncmp(tmp, redir->file, len) == 0)
			break ;
		str = ft_strjoin(tmp, "\n");
		ft_putstr_fd(str, redir->fd);
		free(tmp);
		free(str);
	}
	free(tmp);
	return ;
}

/* << */
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
