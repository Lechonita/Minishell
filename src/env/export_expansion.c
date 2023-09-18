/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:17:08 by lechon            #+#    #+#             */
/*   Updated: 2023/09/18 11:00:11 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Je regarde ce qu'il y a apres le = dans str.
	Si je trouve un $, je prends tout ce qu'il y a derriere ce $ dans un var.
	Je compare ce var avec les names de tous les maillons. Attention on fait rien
	si var = le name de base (lol=$lol).
	Si je trouve same same, expansion. Sinon, do nothing. */

static void export_expansion(t_bigshell *data, t_env *env, char *name)
{
	t_env	*tmp;
	int		i;
	int		j;

	// dprintf(2, "\nEntering export expansion\n");
	tmp = data->env;
	i = 0;
	j = 0;
	// dprintf(2, " env name = %s / env value = %s / name = %s\n",env->name, env->value, name);
	while (tmp)
	{
		// dprintf(2, "   Comparing name -%s- with tmp -%s-\n", name, tmp->name);
		if (ft_strncmp(name, tmp->name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(tmp->name))
		{
			// dprintf(2, "  There is a match !\n");
			// dprintf(2, "    tmp value = %s\n", tmp->value);
			while (tmp->value[i] && tmp->value[i] != '$')
				i++;
			// replace_free_str(tmp->value, env->value, i, (ft_strlen(tmp->value) - ft_strlen(env->name) + 1));
			while (env->value[j])
			{
				tmp->value[i++] = env->value[j++];
				// dprintf(2, "tmp value devient -%s-\n", tmp->value);
			}
			break ;
		}
		tmp = tmp->next;
	}
}

void	compare_env_var(t_bigshell *data, char *var, char *name)
{
	t_env	*env;

	// dprintf(2, "Entering compare env var\n");
	env = data->env;
	while (env)
	{
		// dprintf(2, "  comparing -%s- with -%s-\n", env->name, var);
		if (ft_strncmp(env->name, var, ft_strlen(var)) == 0
			&& ft_strlen(var) == ft_strlen(env->name))
		{
			if (ft_strncmp(env->name, name, ft_strlen(name)) != 0)
				export_expansion(data, env, name);
			break ;
		}
		env = env->next;
	}
}

char	*take_after_dollar(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	i += (str[i] != '\0');
	while (str[i])
	{
		res[j++] = str[i];
		++i;		
	}
	return (res);
}

char	*find_value(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * ft_strlen(str));
	if (!res)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	while (str[++i])
		res[j++] = str[i];
	return (res);
}

char	*find_name(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * ft_strlen(str));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		res[j++] = str[i++];
	}
	return (res);
}
