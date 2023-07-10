/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:17:42 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/05 16:00:43 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

static void	gnl(t_bigshell *data, char *limiter)
{
	int		len;
	char	*str;
	char	*tmp;

	len = ft_strlen(limiter);
	dprintf(2, "limiter = %s, len %d\n", limiter, len);
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
