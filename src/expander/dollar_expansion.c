/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/08/21 16:51:47 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"


t_line	*line_rm_next(t_line *prev)
{
	t_line	*tmp;

	printf("Mon prev = -%c-\n", prev->c);
	if (!prev || !prev->next)
		return (NULL);
	printf("Je suis la et prev->next = %c\n", prev->next->c);
	tmp = prev->next;
	prev->next = prev->next->next;
	free(tmp);
	return (prev->next);
}

void	rm_var_excess(t_bigshell *data, t_line *line, int index, char *var)
{
	t_line	*tmp;
	t_line	*prev;
	int		len;

	if (!data || !line || !var)
		return ;
	printf("Je rentre dans rm excess var avec index = %d\n", index);
	printf("Et je rentre avec line = %c\n", line->c);
	printf("je rentre avec var = %s\n", var);
	tmp = line;
	prev = find_prev(data, tmp->index);
	len = ft_strlen(var) - 1;
	// printf("Avant la boucle while\n");
	// while (tmp && tmp->index != (index + 1))
	// 	tmp = tmp->next;
	// printf("Je sors de la boucle avec tmp = %d\n", tmp->index);
	// if (tmp->index == (index + 2))
	// {
	// 	tmp = tmp->next;
	// 	while (tmp && tmp->index != (index + 1))
	// 		tmp = tmp->next;
	// }
	// printf("Je sors d'un while encore avec tmp = %c\n", tmp->c);
	while (tmp && len >= 0)
	{
		printf("je rentre dans la boucle while avec tmp = %c & len = %d\n", tmp->c, len);
		tmp = line_rm_next(prev);
		printf("Apres le rm node, tmp = %c\n", tmp->c);
		len--;
	}
	printf("Je resors d'un while\n");
	align_line_index(line, 0);
}

void	var_not_found(t_bigshell *data, t_line **line, char *var)
{
	t_line	*tmp;
	t_line	*prev;
	int		len;

	if (!data || !line || !(*line) || !var)
		return ;
	tmp = *line;
	prev = find_prev(data, tmp->index);
	len = ft_strlen(var);
	while (tmp && len >= 0)
	{
		tmp = line_rm_next(prev);
		len--;
	}
	align_line_index(*line, 0);
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
			rm_var_excess(data, line, index, var);
			flag = 0;
			break ;
		}
		env = env->next;
	}
	if (flag == 1)
		var_not_found(data, &line, var);
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

void	dollar_expand(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line	*prev;

	if (!data || !line || !var)
		return ;
	prev = find_prev(data, line->index);
	line = line_rm_next(prev);
	align_line_index(data->line, 0);
	compare_var(data, line, var, index);
}
