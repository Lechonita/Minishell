/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/07/24 18:51:12 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	*token = NULL;
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

void	ft_free_redirection(t_redir **redir)
{
	t_redir	*tmp;

	if (!redir || !(*redir))
		return ;
	while (*redir)
	{
		tmp = (*redir)->next;
		if ((*redir)->fd)
			close((*redir)->fd);
		if ((*redir)->file)
			free((*redir)->file);
		free(*redir);
		(*redir) = tmp;
	}
	*redir = NULL;
}

void	free_all(t_bigshell *data)
{
	if (!data)
		return ;
	if (data->env_paths)
		free_strs(data->env_paths);
	if (data->exec)
		ft_free_exec(&data->exec);
	if (data->token)
		ft_free_token(&data->token);
	if (data->in_out)
		ft_free_redirection(&data->in_out);
	if (data->line)
		ft_free_line(&data->line);
	if (data->env)
		ft_free_env(&data->env);
	rl_clear_history();
	if (data != NULL)
		free(data);
	data = NULL;
}

/*
	if (data->exec->here_doc == 1)
		unlink("minishell_here_doc");
*/