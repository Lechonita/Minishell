/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:58 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/18 14:50:29 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	check_for_expansion(t_bigshell *data, char *str)
// {
// 	char	*name;
// 	char	*value;
// 	char	*var;

// 	value = find_value(str);
// 	if (ft_strchr(value, '$') != NULL)
// 	{
// 		name = find_name(str);
// 		var = take_after_dollar(value);
// 		compare_env_var(data, var, name);
// 		free(name);
// 		free(var);
// 	}
// 	free(value);
// }

// static int	add_len_in_quotes(char *input, int open_quote)
// {
// 	int	size;
// 	int	i;

// 	size = 0;
// 	i = open_quote;
// 	while (input[i] && input[i] != '\n')
// 	{
// 		if (is_single_quote(input[i]) || is_double_quote(input[i]))
// 			break ;
// 		size++;
// 		i++;
// 	}
// 	return (size);
// }

// int	end_pos(char *input, int equal)
// {
// 	int		end;

// 	if (equal == 0)
// 		return (ft_strlen(input) - 1);
// 	end = equal + 1;
// 	while (input[end] && input[end + 1])
// 	{
// 		if ((ft_isalnum(input[end]) || input[end] == '$')
// 			&& !is_single_quote(input[end]) && !is_double_quote(input[end])
// 			&& input[end + 1] != ' ')
// 			end++;
// 		else if (is_single_quote(input[end]) || is_double_quote(input[end]))
// 		{
// 			end += add_len_in_quotes(input, end + 1);
// 			break ;
// 		}
// 		else
// 			break ;
// 	}
// 	return (end);
// }

// int	start_pos(char *input, int equal)
// {
// 	int		start;

// 	if (equal == 0)
// 	{
// 		start = ft_strlen(input);
// 		while (start || input[start])
// 		{
// 			if (input[start] == ' ')
// 				break ;
// 			start--;
// 		}
// 		start += 1;
// 	}
// 	else
// 	{
// 		start = equal - 1;
// 		while (start > 0)
// 		{
// 			if (ft_isalnum(input[start]) && input[start - 1] != ' ')
// 				start--;
// 			else
// 				break ;
// 		}
// 	}
// 	return (start);
// }

char	*find_value(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(char), ft_strlen(str));
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
	res = ft_calloc(sizeof(char), ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		res[j++] = str[i++];
	}
	return (res);
}

static int	find_next_index(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		++i;
	}
	return (i);
}

t_env	*init_var(t_bigshell *data, char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup(name);
	new->to_export = FALSE;
	new->value = ft_strdup(value);
	new->index = find_next_index(data->env);
	new->next = NULL;
	return (new);
}

// int	has_quotes(t_line *line)
// {
// 	while (line)
// 	{
// 		if (line->dq == 2 || line->sq == 2)
// 			return (TRUE);
// 		line = line->next;
// 	}
// 	return (FALSE);
// }

// int	is_export(t_line *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line && i < 6)
// 	{
// 		if (line->c != "export"[i])
// 			return (FALSE);
// 		line = line->next;
// 		i++;
// 	}
// 	return (TRUE);
// }

// void	flag_export_quotes(t_bigshell *data)
// {
// 	t_line	*line;
// 	int		i;

// 	line = data->line;
// 	i = -1;
// 	if (is_export(line) == TRUE)
// 	{
// 		while (line)
// 		{
// 			if (line->sq == 1 || line->sq == 2 || line->dq == 1
// 				|| line->dq == 2)
// 				line->quote_flag = 1;
// 			line = line->next;
// 		}
// 	}
// }
