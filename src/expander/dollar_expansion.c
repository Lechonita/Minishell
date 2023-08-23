/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/08/23 17:09:10 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"


t_line	*line_rm_next(t_line *prev)
{
	t_line	*tmp;

	if (!prev || !prev->next)
		return (NULL);
	tmp = prev->next;
	prev->next = prev->next->next;
	if (tmp)
		free(tmp);
	return (prev->next);
}

t_line	*var_not_found(t_bigshell *data, t_line **line, char *var, int index)
{
	t_line	*tmp;
	t_line	*prev;
	int		len;

	if (!data || !line || !(*line) || !var)
		return (NULL);
	tmp = *line;
	prev = find_prev(data, tmp->index);
	len = ft_strlen(var);
	while (tmp && len >= 0)
	{
		tmp = line_rm_next(prev);
		len--;
	}
	align_line_index(data->line, 0);
	return (find_prev(data, index));
}

t_line	*compare_var(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line	*res;
	t_env	*env;
	int		flag;

	if (!data || !line || !var)
		return (NULL);
	env = data->env;
	flag = 1;
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0
			&& (ft_strlen(env->name) == ft_strlen(var))
			&& env->to_export == FALSE)
		{
			res = add_var(line, env->value, index, var);
			flag = 0;
			break ;
		}
		env = env->next;
	}
	if (flag == 1)
		res = var_not_found(data, &line, var, index);
	align_line_index(data->line, index);
	return (res);
}

t_line	*find_prev(t_bigshell *data, int index)
{
	t_line	*tmp;

	if (!data)
		return (NULL);
	tmp = data->line;
	while (tmp)
	{
		if (tmp->index == index - 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_line	*dollar_expand(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line	*prev;
	t_line	*tmp;

	if (!data || !line || !var)
		return (NULL);
	tmp = line;
	prev = find_prev(data, tmp->index);
	tmp = line_rm_next(prev);
	align_line_index(data->line, 0);
	return (compare_var(data, tmp, var, index));
}
