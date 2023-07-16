/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:13:36 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/15 18:11:43 by Bea              ###   ########.fr       */
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

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !(*cmd))
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->cmd)
			free((*cmd)->cmd);
		if ((*cmd)->cmd_arg)
			free_strs((*cmd)->cmd_arg);
		free((*cmd));
		(*cmd) = tmp;
	}
	*cmd = NULL;
}

void	ft_free_exec(t_exec **exec)
{
	if (!exec || !(*exec))
		return ;
	if ((*exec)->here_doc != 0)
		unlink("minishell_here_doc");
	if ((*exec)->fd_in)
		close((*exec)->fd_in);
	if ((*exec)->fd_out)
		close((*exec)->fd_out);
	if ((*exec)->cmd)
		ft_free_cmd(&(*exec)->cmd);
	free((*exec));
	*exec = NULL;
}
