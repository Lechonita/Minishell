/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:58 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/13 20:43:13 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_existing(t_bigshell *data, char *str)
{
	t_env	*env;

	if (!data || !str)
		return ;
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->name, str) == 0)
		{
			rm_env_el(&env, str);
			break ;
		}
		env = env->next;
	}
}

static int	add_len_in_quotes(char *input, int open_quote)
{
	int	size;
	int	i;

	size = 0;
	i = open_quote;
	while (input[i] && input[i] != '\n')
	{
		if (is_single_quote(input[i]) || is_double_quote(input[i]))
			break ;
		size++;
		i++;
	}
	return (size);
}

int	end_pos(char *input, int equal)
{
	int		end;

	if (equal == 0)
		return (ft_strlen(input) - 1);
	end = equal + 1;
	while (input[end] && input[end + 1])
	{
		if (ft_isalnum(input[end]) && !is_single_quote(input[end])
			&& !is_double_quote(input[end]) && input[end + 1] != ' ')
			end++;
		else if (is_single_quote(input[end]) || is_double_quote(input[end]))
		{
			end += add_len_in_quotes(input, end + 1);
			break ;
		}
		else
			break ;
	}
	return (end);
}

int	start_pos(char *input, int equal)
{
	int		start;

	if (equal == 0)
	{
		start = ft_strlen(input);
		while (start || input[start])
		{
			if (input[start] == ' ')
				break ;
			start--;
		}
		start += 1;
	}
	else
	{
		start = equal - 1;
		while (start > 0)
		{
			if (ft_isalnum(input[start]) && input[start - 1] != ' ')
				start--;
			else
				break ;
		}
	}
	return (start);
}

int	is_export(t_line *line)
{
	t_line	*tmp;
	int		i;
	char	*res;

	if (!line)
		return (FALSE);
	tmp = line;
	i = 0;
	res = "export";
	while (tmp && i < 6)
	{
		if (tmp->c != res[i])
			return (FALSE);
		tmp = tmp->next;
		i++;
	}
	if (tmp)
		return (TRUE);
	return (FALSE);
}
