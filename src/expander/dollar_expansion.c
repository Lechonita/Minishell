/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/18 16:02:02 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

t_line	*line_new_var(t_line *line, t_line *next, char c)
{
	t_line	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->index = 0;
	new->type = WORD;
	new->dq = line->dq;
	new->sq = line->sq;
	new->c = c;
	new->next = next;
	return (new);
}

t_line	*line_add_node(t_line *line, char value, int index)
{
	if (!line)
		return (NULL);
	while (line && line->next && line->index != index)
		line = line->next;
	line->next = line_new_var(line, line->next, value);
	return (line);
}

void	add_var(t_line *line, char *value, int idx, char *var)
{
	t_line	*tmp;
	int		i;
	int		len;

	if (!line || !value || !idx || !var)
		return ;
	tmp = line;
	i = 0;
	len = ft_strlen(var);
	while (value[i])
	{
		// if (len > 0)
		// {
		// 	tmp->type = WORD;
		// 	tmp->c = value[i];
		// 	tmp = tmp->next;
		// }
		// else
			tmp = line_add_node(tmp, value[i], idx);
		// if (tmp->next && tmp->next->type != BLANK)
		// 	tmp->next = tmp->next->next;
		print_t_line(line);
		align_line_index(line);
		i++;
		len--;
		idx++;
	}
}

void	var_not_found(t_line **line, char *var)
{
	t_line	*tmp;
	int		acolade;
	int		len;

	if (!line || !(*line) || !var)
		return ;
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
	return ;
}

void	compare_var(t_bigshell *data, t_line *line, char *var, int index)
{
	t_env		*env;
	int			flag;

	if (!data || !line || !var | !index)
		return ;
	env = data->env;
	flag = 1;
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0)
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
	int		i;

	if (!data || !line || !var | !index)
		return ;
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
