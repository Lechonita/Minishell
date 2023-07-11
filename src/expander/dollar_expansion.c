/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:32:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/11 18:56:17 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

t_line	*add_var(t_bigshell *data, t_line *line, char *value)
{
	t_line	*tmp;
	int		i;

	printf(">> Je rentre dans la fonction add_var\n");
	if (!data || !line || !value)
		return (NULL);
	tmp = line;
	i = 0;
	printf("Mon value = %s\n", value);
	while (value[i])
	{
		printf("	Mon value[%d] = %c\n", i, value[i]);
		tmp = line_new(tmp, value[i], tmp->index);
		i++;
	}
	printf("Je sors de la boucle while avant de remettre les index\n");
	align_line_index(data);
	printf("Jái remis les index\n<< Et je sors de la fonction\n");
	return (tmp);
}

t_line	*compare_var(t_bigshell *data, t_line *line, char *var)
{
	t_line		*tmp;
	t_bigshell	*bis;

	printf(">> Je rentre dans la fonction compare_var\n");
	if (!line || !var)
		return (NULL);
	tmp = line;
	bis = data;
	printf("Juste avant de rentrer dans la boucle while env\n");
	while (bis->env)
	{
		printf("	Ensuite je rentre dans la boucle bis->env->name = %s\n", bis->env->name);
		printf("Ca donne quoi ca %d\n", ft_strncmp(bis->env->name, var, ft_strlen(var)));
		if (ft_strncmp(bis->env->name, var, ft_strlen(var)) == 0)
		{
			printf("Je rentre dans le if !\n");
			tmp = add_var(bis, tmp, bis->env->value);
			break ;
		}
		bis->env = bis->env->next;
	}
	printf("<< Ensuite je sors de compare_var\n");
	return (tmp);
}

t_line	*dollar_expand(t_bigshell *data, t_line *line, char *var)
{
	t_line	*tmp;
	int		i;

	printf(" ==> JE RENTRE ICI <==\n");
	if (!line)
		return (NULL);
	tmp = line->next;
	i = 0;
	printf("Avant de rentrer dans la boucle, mon tmp->c = %c\n", tmp->c);
	if (tmp->c == 123)
	{
		printf("Je passe par la !!!!!\n");
		tmp = tmp->next;
		while (var[i])
		{
			if (var[i] == '}')
				var[i] = '\0';
			i++;
		}
		tmp = compare_var(data, tmp, var + 1);
	}
	else
		tmp = compare_var(data, tmp, var);
	printf("A la fin de dollar expand, mon var = %s\n", var);
	return (tmp);
}
