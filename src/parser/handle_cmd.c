/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:57:52 by Bea               #+#    #+#             */
/*   Updated: 2023/09/13 09:11:08 by bebigel          ###   ########.fr       */
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
		if ((tok->aim == SIMPLE_CMD || tok->aim == BUILTIN)
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
