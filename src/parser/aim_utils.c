/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:20:03 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/13 15:57:20 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

char	*join_space(char *s1, char *s2, char *to_add)
{
	char	*tmp;
	char	*str;

	tmp = free_strjoin(s1, to_add);
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

int	last_is_dollar(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '$')
		return (1);
	return (0);
}

void	rm_blank(t_bigshell *data)
{
	t_token	*tok;

	if (!data->token || !data->token->next)
		return ;
	tok = data->token;
	while (tok != NULL && tok->next != NULL)
	{
		if (tok->next->type == BLANK)
			token_rm_next(tok);
		tok = tok->next;
	}
}
