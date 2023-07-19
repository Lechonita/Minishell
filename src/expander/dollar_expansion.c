/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/19 15:57:43 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

t_line	*line_new_var(t_line *line, t_line *next, char c)
{
	t_line	*new;

	printf("Est-ce que ca vient rajouter ici ?\n");
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->index = 0;
	new->type = WORD;
	if (line)
	{
		new->dq = line->dq;
		new->sq = line->sq;
	}
	else
	{
		new->dq = 0;
		new->sq = 0;
	}
	new->c = c;
	new->next = next;
	return (new);
}

t_line	*line_add_node(t_line *line, char value, int index)
{
	printf("Je passe au moins par la avec un index de %d\n", index);
	if (!line)
		line = line_new_var(line, NULL, value);
	else
	{
		while (line && line->next && line->index != index)
			line = line->next;
		printf("Une fois la boucle finie, je suis sur %c\n", line->c);
		line->next = line_new_var(line, line->next, value);
	}
	return (line);
}

t_line	*line_replace_node(t_line *line, char value, int index)
{
	if (!line || !value || !index)
		return (NULL);
	line->c = value;
	line->type = WORD;
	return (line);
}

t_line	*check_next_node(t_line *line)
{
	t_line	*tmp;

	tmp = line;
	if (tmp->next)
		return (tmp->next);
	return (NULL);
}

void	add_var(t_line *line, char *value, int idx, char *var)
{
	t_line	*tmp;
	int		i;
	int		j;

	if (!line || !value || !idx || !var)
		return ;
	tmp = line->next;
	i = -1;
	j = 0;
	while (value[++i])
	{
		
		printf("Index = %d\n", idx);
		if (var[j] && tmp->c == var[j])
		{
			printf("Est-ce que je passe par la ?\n");
			tmp = line_replace_node(tmp, value[i], idx);
			tmp = tmp->next;
			j++;
		}
		else
		{
			printf("A ce niveau la\n");
			tmp = line_add_node(tmp, value[i], idx);
			// tmp = line_new_var(tmp, check_next_node(tmp), value[i]);
		}
			idx++;
		print_t_line(line);
		printf(" Segfault par la ?\n");
	}
		// align_line_index(line, idx);
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
