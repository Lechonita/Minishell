/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:37:34 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/24 12:10:02 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	is_word_before_equal(t_line *line, int eq_is_here)
{
	t_line	*tmp;
	int		count;

	tmp = line;
	count = 0;
	while (tmp && count < eq_is_here)
	{
		if (tmp->type == WORD && count == eq_is_here - 1)
			return (TRUE);
		tmp = tmp->next;
		count++;
	}
	return (FALSE);
}

int	is_word_after_equal(t_line *line, int eq_is_here)
{
	t_line	*tmp;
	int		count;

	tmp = line;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD && count == eq_is_here + 1)
			return (TRUE);
		tmp = tmp->next;
		count++;
	}
	return (FALSE);
}

void	add_to_env(t_bigshell *data, t_line *line)
{
	t_line	*tmp;
	int		equal_is_here;
	char	*key;
	char	*value;

	tmp = line;
	equal_is_here = check_equal(line);
	key = ft_substr(line_to_str(line), 0, equal_is_here);
	value = ft_substr(line_to_str(line), equal_is_here + 1,
			ft_strlen(line_to_str(line)) - equal_is_here);
	if (is_word_before_equal(line, equal_is_here)
		&& is_word_after_equal(line, equal_is_here))
	{
		if (ft_strncmp(key, "PATH", ft_strlen(key)) == 0)
			data->path = ft_split(value, ':');
		else
			add_env_var(data, key, value);
	}
	else
		dprintf(2, "export: not a valid identifier\n");
	free(key);
	free(value);
}

void	check_for_export(t_bigshell *data, t_line *line)
{
	int	equal_is_here;

	equal_is_here = check_equal(line);
	if (is_word_before_equal(line, equal_is_here)
		&& is_word_after_equal(line, equal_is_here))
		add_to_env(data, line);
	else
		dprintf(2, "export: not a valid identifier\n");
}
