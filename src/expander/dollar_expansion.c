/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/27 16:59:30 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

void	rm_var_excess(t_line *line, int index, char *var)
{
	t_line	*tmp;
	int		len;

	if (!line || !var)
		return ;
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
		tmp->c = 11;
		tmp = tmp->next;
		len--;
	}
}

void	var_not_found(t_line **line, char *var)
{
	t_line	*tmp;
	int		len;

	if (!line || !(*line) || !var)
		return ;
	tmp = *line;
	len = get_var_len(tmp);
	while (tmp && len > 0)
	{
		tmp->type = BLANK;
		tmp->c = 11;
		tmp = tmp->next;
		len--;
	}
	print_t_line(*line);
}

void	compare_var(t_bigshell *data, t_line *line, char *var, int index)
{
	t_env	*env;
	int		flag;

	if (!data || !line || !var)
		return ;
	env = data->env;
	flag = 1;
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0
			&& (ft_strlen(env->name) == ft_strlen(var))
			&& env->to_export == FALSE)
		{
			add_var(line, env->value, index, var);
			flag = 0;
			break ;
		}
		env = env->next;
	}
	if (flag == 1)
		var_not_found(&line, var);
}

void	dollar_expand(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line	*tmp;

	if (!data || !line || !var)
		return ;
	tmp = line;
	tmp->type = BLANK;
	tmp->c = 11;
	tmp = line->next;
	compare_var(data, line, var, index);
}
