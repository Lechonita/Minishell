/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:13:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/12 14:44:45 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

void	verify_pipes(t_bigshell *data, int counter, int i)
{
	t_line	*tmp;

	if (!data || !data->line)
		return ;
	tmp = data->line;
	while (tmp)
	{
		if (tmp->c == '|')
		{
			if (i == 0 || counter == i - 1)
			{
				ft_free_line(&data->line);
				ft_error(2, W_PIPE);
				break ;
			}
			counter = i;
		}
		if (tmp->type != BLANK)
			i++;
		tmp = tmp->next;
	}
}

void	token_group(t_token *tok)
{
	t_token	*el;
	int		grp;

	el = tok;
	grp = 0;
	while (el != NULL)
	{
		if (el->type == PIPE)
			grp++;
		el->group = grp;
		el = el->next;
	}
	g_global.nb_cmd = grp + 1;
}

int	token_size(t_line *current)
{
	int		size;
	t_line	*el;

	size = 1;
	el = current;
	while (el->next && el->type == el->next->type)
	{
		size++;
		el = el->next;
	}
	return (size);
}

char	*token_value(t_line *current)
{
	t_line	*el;
	char	*value;
	int		size;
	int		i;

	i = 0;
	el = current;
	size = token_size(current);
	value = ft_calloc(sizeof(char *), size + 1);
	while (el != NULL && i < size)
	{
		value[i] = el->c;
		i++;
		el = el->next;
	}
	value[i] = '\0';
	return (value);
}

void	find_tokens(t_bigshell *data)
{
	t_line	*el;
	char	*value;
	int		token_size;
	int		pos;

	if (!data || !data->line)
		return ;
	el = data->line;
	pos = -1;
	while (el != NULL)
	{
		value = token_value(el);
		token_size = ft_strlen(value);
		create_token(data, el, value, ++pos);
		while (el->next && token_size-- > 1)
			el = el->next;
		free(value);
		el = el->next;
	}
}
