/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:13:36 by bebigel           #+#    #+#             */
/*   Updated: 2023/08/30 17:36:27 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs != NULL)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	ft_free_simple_cmd(t_simple_cmd **simple_cmd)
{
	t_simple_cmd	*tmp;

	if (!simple_cmd || !(*simple_cmd))
		return ;
	while (*simple_cmd)
	{
		tmp = (*simple_cmd)->next;
		if ((*simple_cmd)->cmd)
			free((*simple_cmd)->cmd);
		if ((*simple_cmd)->cmd_arg)
			free_strs((*simple_cmd)->cmd_arg);
		if ((*simple_cmd)->redir)
			ft_free_redirection(&(*simple_cmd)->redir);
		if ((*simple_cmd)->fd_in)
			close((*simple_cmd)->fd_in);
		if ((*simple_cmd)->fd_out)
			close((*simple_cmd)->fd_out);
		free((*simple_cmd));
		(*simple_cmd) = tmp;
	}
	(*simple_cmd) = NULL;
}
