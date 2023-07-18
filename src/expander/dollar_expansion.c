/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/18 15:31:31 by jrouillo         ###   ########.fr       */
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
	// line->next = line_new(line, value, 0);
	line->next = line_new_var(line, line->next, value);
	return (line);
}

/* A revoir parce qu'on perd les maillons d'après une fois qu'on appelle
	line_add_node */

void	add_var(t_bigshell *data, t_line *line, char *value, int idx)
{
	t_line	*tmp;
	int		i;

	if (!data || !line || !value || !idx)
		return ;
	tmp = line;
	i = 0;
	printf("Mon value = %s\n", value);
	while (value[i])
	{
		tmp = line_add_node(tmp, value[i], idx);
		print_t_line(line);
		align_line_index(data);
		i++;
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

	// printf("\nA l'entrée de compare_var, avant de COMMENCER ===>\n");
	// print_t_line(line);
	if (!data || !line || !var | !index)
		return ;
	env = data->env;
	flag = 1;
	printf("Mon var = %s\n", var);
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0)
		{
			add_var(data, line, env->value, index);
			flag = 0;
			break ;
		}
		env = env->next;
	}
	if (flag == 1)
		var_not_found(&line, var);
	// printf("\nA la fin de compare_var, avant de rendre a do_expansion ===>\n");
	// print_t_line(line);
}

void	dollar_expand(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line	*tmp;
	int		i;

	// printf("\nA l'entrée de dollar_expand, avant de COMMENCER ===>\n");
	// print_t_line(line);
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
	// printf("\nA la fin de dollar_expand, avant de rendre a do_expansion ===>\n");
	// print_t_line(line);
}
