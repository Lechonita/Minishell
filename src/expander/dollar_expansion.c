/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/20 15:28:38 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

void rm_var_excess(t_line *line, int index, char *var)
{
	t_line *tmp;
	int len;

	if (!line || !var)
		return;
	tmp = line;
	len = ft_strlen(var) - 1;
	while (tmp && tmp->index != (index + 2))
		tmp = tmp->next;
	if (tmp->index == (index + 2))
	{
		tmp = tmp->next;
		while (tmp && tmp->index != (index + 2))
			tmp = tmp->next;
	}
	while (tmp && len > 0)
	{
		tmp->type = BLANK;
		tmp->c = ' ';
		tmp = tmp->next;
		len--;
	}
}

void add_var(t_line *line, char *value, int idx, char *var)
{
	t_line *tmp;
	int index;
	int i;
	int j;

	if (!line || !value || !idx || !var)
		return;
	tmp = line->next;
	index = idx;
	i = -1;
	j = 0;
	while (value[++i])
	{
		if (var[j] && tmp->c == var[j] && j == 0)
		{
			tmp = line_replace_node(tmp, value[i], idx);
			j++;
		}
		else
			tmp = line_add_node(tmp, value[i], idx);
		idx++;
	}
	rm_var_excess(line, index, var);
	// align_line_index(line, idx);
}

void var_not_found(t_line **line, char *var)
{
	t_line *tmp;
	int acolade;
	int len;

	if (!line || !(*line) || !var)
		return;
	tmp = *line;
	acolade = 0;
	if (tmp->c == '{')
		acolade = 1;
	len = get_var_len(tmp, acolade);
	while (tmp && len > 0)
	{
		tmp->type = BLANK;
		tmp->c = ' ';
		tmp = tmp->next;
		len--;
	}
	return;
}

void compare_var(t_bigshell *data, t_line *line, char *var, int index)
{
	t_env *env;
	int flag;

	if (!data || !line || !var | !index)
		return;
	env = data->env;
	flag = 1;
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0)
		{
			add_var(line, env->value, index, var);
			flag = 0;
			break;
		}
		env = env->next;
	}
	if (flag == 1)
		var_not_found(&line, var);
}

void dollar_expand(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line *tmp;
	int i;

	if (!data || !line || !var | !index)
		return;
	tmp = line->next;
	i = 0;
	if (tmp->c == 123)
	{
		tmp = tmp->next;
		while (var[i])
		{
			if (var[i] == '}')
				var[i] = '\0';
			i++;
		}
		compare_var(data, line, var + 1, index);
	}
	else
		compare_var(data, line, var, index);
}
