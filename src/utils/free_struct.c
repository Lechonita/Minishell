/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/07/04 16:31:42 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Sert a supprimer un maillon de la liste t_line. Fonction utilisee dans 
	la gestion des open quotes (voir expander). */

// void	ft_free_line_node(t_line *line)
// {
// 	if (!line)
// 		return ;
// 	if (line->c)
// 		free(line->c);
// 	free(line);
// 	line = NULL;
// }

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

/* Fonction qui free tous les maillons de la liste chainee t_env. */
void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !(*env))
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->name)
		{
			free((*env)->name);
			(*env)->name = NULL;
		}
		free(*env);
		(*env) = tmp;
	}
	*env = NULL;
}

void	ft_free_token(t_token **token)
{
	t_token	*tmp;

	if (!(*token) || !token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		if ((*token)->value)
			free((*token)->value);
		free((*token));
		(*token) = tmp;
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
}

void	ft_free_line(t_line **line)
{
	t_line	*tmp;

	if (!line || !(*line))
		return ;
	while (*line)
	{
		tmp = (*line)->next;
		free(*line);
		(*line) = tmp;
	}
	*line = NULL;
}

void	free_all(t_bigshell *data)
{
	if (!data)
		return ;
	if (data->exec->fd_in)
		close(data->exec->fd_in);
	if (data->exec->fd_out)
		close(data->exec->fd_out);
	// if (data->exec->here_doc == 1)
	// 	unlink("/tmp/.minishell_here_doc");
	if (data->history)
		free_strs(data->history);
	if (data->env_paths)
		free_strs(data->env_paths);
	if (data->exec->cmd)
		ft_free_cmd(&data->exec->cmd);
	if (data->exec)
		free(data->exec);
	if (data->token)
		ft_free_token(&data->token);
	if (data->line)
		ft_free_line(&data->line);
	if (data->env)
		ft_free_env(&data->env);
	free(data);
	data = NULL;
	rl_clear_history();
}
