/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/20 14:36:33 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

// void	rm_var_excess(t_line *line, int index, char *var)
// {
// 	t_line	*tmp;
// 	int		len;

// 	if (!line || !var)
// 		return ;
// 	tmp = line;
// 	len = ft_strlen(var) - 1;
// 	printf("Mon var c'est %s et sa len c'est %d\n", var, len);
// 	printf("aussi l'index c'est %d\n", index);
// 	while (tmp && tmp->index != index - 2)
// 		tmp = tmp->next;
// 	printf("La je suis sur %c\n", tmp->c);
// 	if (tmp->index == index - 2)
// 	{
// 		tmp = tmp->next;
// 		while (tmp->index != index - 2)
// 		tmp = tmp->next;
// 	}
// 	printf("La je suis sur le tmp -%c-\n", tmp->c);
// 	while (tmp && len > 0)
// 	{
// 		tmp->type = BLANK;
// 		tmp->c = ' ';
// 		printf("Et je l'ai transorme en -%c-\n", tmp->c);
// 		tmp = tmp->next;
// 		len--;
// 	}
// }

t_line	*line_new_var(t_line *line, t_line *after, char c, int index)
{
	t_line	*new;

	// printf("	Et je passe par line new var pour rajouter le node %c\n", c);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	// printf("	Et je lui donne un index de %d\n", index + 1);
	new->index = index + 1;
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
	new->next = after;
	return (new);
}

t_line	*line_add_node(t_line *line, char value, int index)
{
	// printf("Je passe par la fonction add node avec un index de %d\n", index);
	if (!line)
		line = line_new_var(line, NULL, value, index);
	else
	{
		while (line && line->next && line->index != index)
			line = line->next;
		// printf("Une fois la boucle finie, je suis sur %c\n", line->c);
		line->next = line_new_var(line, line->next, value, index);
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

void	add_var(t_line *line, char *value, int idx, char *var)
{
	t_line	*tmp;
	int		index;
	int		i;
	int		j;

	if (!line || !value || !idx || !var)
		return ;
	tmp = line->next;
	index = idx;
	i = -1;
	j = 0;
	printf("\nAu tout debut, t_line c'est ====>\n");
	print_t_line(line);
	while (value[++i])
	{
		// printf("En debut de boucle, Index = %d\n", idx);
		// printf("Mon var[%d] = %c  et mon tmp = %c\n", j, var[j], tmp->c);
		if (var[j] && tmp->c == var[j] && j == 0)
		{
			// printf("Je m'apprete a remplacer le node %c\n", tmp->c);
			tmp = line_replace_node(tmp, value[i], idx);
			j++;
		}
		else
		{
			// printf("Je m'apprete a rajouter un node\n");
			tmp = line_add_node(tmp, value[i], idx);
		}
			// tmp = tmp->next;
		idx++;
		print_t_line(line);
	}
	// rm_var_excess(line, index, var);
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
