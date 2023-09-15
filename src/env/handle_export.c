/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:37:34 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/15 16:02:57 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_equal(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '=' && (!input[i + 1] || input[i + 1] != '='))
			count++;
		i++;
	}
	return (count);
}

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

void	remove_quotes(char *str)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != '\"' && str[i] != '\'')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

static void	add_to_env(t_bigshell *data, int equal, char *input)
{
	char	*str;
	char	*name;
	int		pos[2];
	int		env_size;
	t_env	*tmp;

	env_size = 0;
	pos[0] = start_pos(input, equal);
	pos[1] = end_pos(input, equal) + 1;
	str = ft_substr(input, pos[0], pos[1] - pos[0]);
	if (ft_strchr(str, '\"') != NULL || ft_strchr(str, '\'') != NULL)
		remove_quotes(str);
	name = ft_substr(str, 0, ft_strchr(str, '=') - str);
	unset_var(name, NULL, data);
	tmp = data->env;
	while (tmp)
	{
		env_size++;
		tmp = tmp->next;
	}
	env_addback(&data->env, env_new(str, env_size, TRUE));
	free(str);
	free(name);
}

void	check_for_export(t_bigshell *data, t_line *line, char *input)
{
	int	equal_is_here;
	int	nb_of_equal;

	equal_is_here = 0;
	nb_of_equal = count_equal(input);
	if (nb_of_equal == 0)
	{
		if (is_export(input) == TRUE)
			add_to_env(data, equal_is_here, input);
		return ;
	}
	while (nb_of_equal-- > 0 && ft_strncmp(input, "export ", 7) == 0)
	{
		while (input[equal_is_here] && input[equal_is_here] != '=')
			equal_is_here++;
		if (input[equal_is_here - 1] == ' ')
			ft_error(1, "Minishell: not a valid identifier\n");
		if (equal_is_here == ft_strlen(input))
			return ;
		if (is_word_near_equal(line, equal_is_here, 1) == TRUE
			&& is_word_near_equal(line, equal_is_here, -1) == TRUE)
			add_to_env(data, equal_is_here, input);
		equal_is_here = end_pos(input, equal_is_here) + 1;
	}
}
