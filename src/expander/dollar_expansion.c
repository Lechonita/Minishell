/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/20 17:58:10 by lechon           ###   ########.fr       */
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
		// if (tmp->c != 39)
		// {
			tmp->type = BLANK;
			tmp->c = ' ';
			tmp = tmp->next;
			len--;
		// }
	}
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
	t_env 	*env;
	int 	flag;

	if (!data || !line || !var | !index)
		return;
	env = data->env;
	flag = 1;
	// printf("===> Au milieu (compare_var), on a :\n");
	// print_t_line(line);
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0
			&& (ft_strlen(env->name) == ft_strlen(var)))
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

void	rm_dollar(t_line *line)
{
	t_line	*tmp;

	if (!line || !line->next)
		return ;
	// printf("La je suis sur %c\n", line->c);
	tmp = line;
	line = line->next;
	free(tmp);
}

void dollar_expand(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line *tmp;
	int i;

	if (!data || !line || !var | !index)
		return;
	rm_dollar(line);
	// print_t_line(line);
	tmp = line->next;
	printf("Et maintenant mon tmp c'est %c\n", tmp->c);
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
