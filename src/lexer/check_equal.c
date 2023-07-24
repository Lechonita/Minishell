/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:37:34 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/24 18:59:04 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_word_near_equal(t_line *line, int eq_is_here, int direction)
{
	t_line	*tmp;
	int		count;

	tmp = line;
	count = 0;
	while (tmp)
	{
		if (direction > 0 && (tmp->type == WORD || tmp->type == SQUOTE
				|| tmp->type == DQUOTE) && count == eq_is_here + 1)
			return (TRUE);
		else if (direction < 0 && tmp->type == WORD && count == eq_is_here - 1)
			return (TRUE);
		tmp = tmp->next;
		count++;
	}
	return (FALSE);
}

int	add_len_in_quotes(char *input, int open_quote)
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

int	export_size(char *input, int equal, int direction)
{
	int		start;
	int		end;

	start = equal - 1;
	end = equal + 1;
	while (start > 0)
	{
		if (ft_isalnum(input[start]) && input[start - 1] != ' ')
			start--;
		else
			break ;
	}
	while (input[end + 1])
	{
		if (ft_isalnum(input[end]) && !is_single_quote(input[end])
			&& !is_double_quote(input[end]) && input[end + 1] != ' ')
			end++;
		else if (is_single_quote(input[end]) || is_double_quote(input[end]))
			end += add_len_in_quotes(input, end + 1);
		else
			break ;
	}
	if (direction > 0)
		return (end);
	else
		return (start);
}

void	add_to_env(t_bigshell *data, int equal, char *input)
{
	char	*str;
	int		start;
	int		end;
	int		env_size;
	t_env	*tmp;

	start = export_size(input, equal, -1);
	end = export_size(input, equal, 1);
	env_size = 0;
	tmp = data->env;
	while (tmp)
	{
		env_size++;
		tmp = tmp->next;
	}
	dprintf(2, "start/end = %d/%d\n", start, end);
	dprintf(2, "env size = %d\n", env_size);
	str = ft_substr(input, start, end - start);
	dprintf(2, "str = %s\n", str);
	env_addback(data->env, env_new(str, env_size, TRUE));
	free(str);
}

void	check_for_export(t_bigshell *data, t_line *line, char *input)
{
	int	equal_is_here;

	equal_is_here = 0;
	while (input[equal_is_here] && input[equal_is_here] != '=')
		equal_is_here++;
	if (is_word_near_equal(line, equal_is_here, 1)
		&& is_word_near_equal(line, equal_is_here, -1))
		add_to_env(data, equal_is_here, input);
	else
		dprintf(2, "export: not a valid identifier\n");
	print_env(data);
}

/*
int	check_equal(t_line *line)
{
	t_line	*tmp;
	int		count;

	tmp = line;
	count = 0;
	while (tmp)
	{
		if (tmp->c == '=')
			return (count);
		tmp = tmp->next;
		count++;
	}
	return (FALSE);
}
*/