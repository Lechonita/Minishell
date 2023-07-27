/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:13:36 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/27 14:56:26 by bebigel          ###   ########.fr       */
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
		// if ((*simple_cmd)->in_file)
		// 	free((*simple_cmd)->in_file);
		// if ((*simple_cmd)->out_file)
		// 	free((*simple_cmd)->out_file);
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
	if ((*exec)->fd_in)
		close((*exec)->fd_in);
	if ((*exec)->fd_out)
		close((*exec)->fd_out);
	if ((*exec)->cmd)
		ft_free_cmd(&(*exec)->cmd);
	if ((*exec)->here_doc != 0)
		unlink("minishell_here_doc");
	free((*exec));
	*exec = NULL;
}
