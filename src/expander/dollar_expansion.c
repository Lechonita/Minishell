/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/17 17:26:40 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

t_line	*line_add_node(t_line *line, char value, int index)
{
	if (!line)
		return (NULL);
	while (line && line->next && line->index != index)
		line = line->next;
	line->next = line_new(line, value, 0);
	return (line);
}

void	add_var(t_bigshell *data, t_line *line, char *value, int index)
{
	t_line	*tmp;
	int		i;

	print_t_line(line);
	if (!data || !line || !value)
		return ;
	tmp = line;
	i = 0;
	while (value[i])
	{
		tmp = line_add_node(tmp, value[i], index);
		align_line_index(data);
		i++;
		index++;
	}
	print_t_line(line);
}

void	var_not_found(t_line *line, char *var)
{
	t_line	*tmp;
	t_line	*prochain;
	int		acolade;
	int		len;

	if (!line || !var)
		return ;
	printf("Au tout debut, mon line->c = %c\n", line->c);
	tmp = line;
	acolade = 0;
	if (tmp->c == '{')
		acolade = 1;
	len = get_var_len(tmp, acolade);
	printf("Ensuite, ma len = %d\n", len);
	while (tmp && len > 0)
	{
		prochain = tmp->next;
		printf("Mon prochain->c devient = %c\n", prochain->c);
		free(tmp);
		len--;
		tmp = prochain;
		printf("Et mon tmp a la fin de la boucle cest %c\n", tmp->c);
	}
}

void	compare_var(t_bigshell *data, t_line *line, char *var, int index)
{
	t_bigshell	*bis;
	int			flag;

	if (!line || !var)
		return ;
	bis = data;
	flag = 1;
	while (bis->env)
	{
		if (ft_strncmp(bis->env->name, var, ft_strlen(var)) == 0)
		{
			add_var(bis, line, bis->env->value, index);
			flag = 0;
			break ;
		}
		bis->env = bis->env->next;
	}
	if (flag == 1)
		var_not_found(line, var);
}

void	dollar_expand(t_bigshell *data, t_line *line, char *var, int index)
{
	t_line	*tmp;
	int		i;

	if (!line)
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
