/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:57:52 by Bea               #+#    #+#             */
/*   Updated: 2023/07/28 18:26:59 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_cmd_by_grp(t_token *token, int group)
{
	t_token	*tok;
	int		count;

	tok = token;
	count = 0;
	while (tok != NULL)
	{
		if ((tok->aim == SIMPLE_CMD  || tok->aim == BUILTIN)
			&& tok->group == group)
			count++;
		tok = tok->next;
	}
	return (count);
}

static void	join_cmds(t_token *token, int group, int count)
{
	int		i;
	t_token	*tmp;
	char	*str;

	i = 0;
	tmp = token;
	str = ft_strdup("");
	while (i < count && tmp->group == group)
	{
		str = free_strjoin(str, tmp->value);
		if (i < count - 1)
			str = free_strjoin(str, " ");
		tmp = tmp->next;
		i++;
	}
	free(token->value);
	token->value = ft_strdup(str);
	free(str);
	if (token->aim == BUILTIN)
		token->aim = BUILTIN;
	else
		token->aim = SIMPLE_CMD;
	while (i-- > 1)
		token_rm_next(token);
}

static void	merge_cmd(t_token *token)
{
	int		group;
	int		count;
	t_token	*tmp;
	
	tmp = token;
	group = 0;
	while (group < g_global.nb_cmd)
	{
		count = 0;
		count = count_cmd_by_grp(token, group);
		if (count > 1)
		{
			while (tmp != NULL && tmp->group != group)
				tmp = tmp->next;
			join_cmds(tmp, group, count);
		}
		group++;
	}
}

void	merge_token_cmd(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL && tok->next != NULL)
	{
		while ((tok->next->aim != SIMPLE_CMD && tok->next->aim != BUILTIN)
			&& tok->next != NULL && tok != NULL)
		{
			token_rm_next(tok);
			if (tok->next == NULL)
				break ;
			if (tok->next->type == SIMPLE_CMD || tok->next->type == BUILTIN)
				tok = tok->next;
		}
		tok = tok->next;
	}
	merge_cmd(data->token);
}

void	add_cmd_to_cmd(t_bigshell *data)
{
	t_token			*tok;
	t_simple_cmd	*simple_cmd;
	
	simple_cmd = data->simple_cmd;
	while (simple_cmd != NULL)
	{
		tok = data->token;
		while (tok)
		{
			if ((tok->aim == SIMPLE_CMD || tok->aim == BUILTIN)
				&& tok->group == simple_cmd->idx)
			{
				simple_cmd->cmd = ft_strdup(tok->value);
				if (!simple_cmd->cmd)
					ft_error(EXIT_FAILURE, W_LST_CMD_DUP);
				simple_cmd->cmd_arg = ft_split(tok->value, ' ');
				if (!simple_cmd->cmd_arg)
					ft_error(EXIT_FAILURE, W_SPLIT_CMD);
				if (tok->aim == BUILTIN)
					simple_cmd->builtin = TRUE;
			}
			tok = tok->next;
		}
		simple_cmd = simple_cmd->next;
	}
}
