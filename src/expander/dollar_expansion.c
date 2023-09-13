/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/13 13:30:35 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

void	remove_rest(t_line *line, int value, int var)
{
	t_line	*tmp;

	if (!line || var < value)
		return ;
	tmp = line;
	while (tmp && value < var)
	{
		tmp->quote_flag = 1;
		tmp = tmp->next;
		value++;
	}
}

t_line	*line_rm_next(t_line *prev)
{
	t_line	*tmp;

	if (!prev || !prev->next)
		return (NULL);
	if (prev->c == '$')
		prev->quote_flag = 1;
	else
	{
		tmp = prev->next;
		prev->next = prev->next->next;
		if (tmp)
			free(tmp);
	}
	return (prev->next);
}

t_line	*find_prev(t_bigshell *data, int index)
{
	t_line	*tmp;

	if (!data)
		return (NULL);
	tmp = data->line;
	if (index == 0)
		return (tmp);
	while (tmp)
	{
		if (tmp->index == index - 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_line	*var_not_found(t_bigshell *data, t_line **line, char *var, int index)
{
	t_line	*tmp;
	int		len;

	if (!data || !line || !(*line) || !var)
		return (NULL);
	tmp = *line;
	len = ft_strlen(var);
	if (index == 0)
		len += 1;
	while (tmp && len >= 0)
	{
		tmp->quote_flag = 1;
		tmp = tmp->next;
		len--;
	}
	align_line_index(data->line, 0);
	return (*line);
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
		if (ft_strlen(env->name) == ft_strlen(var)
			&& ft_strcmp(env->name, var) == 0 && env->to_export == FALSE)
		{
			line = line_rm_next(find_prev(data, line->index));
			res = add_var(line, env->value, var);
			flag = 0;
			break ;
		}
		env = env->next;
	}
	if (flag == 1)
		res = var_not_found(data, &line, var, index);
	align_line_index(data->line, index - 1);
	return (res);
}
