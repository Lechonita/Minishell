/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caracter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:47:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/14 15:39:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	verify_point(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	if (tmp[0] == '.' && tmp[1] == '\0')
	{
		free(tmp);
		ft_error(2, W_POINT);
		return (FALSE);
	}
	if (tmp[0] == '.' && tmp[1] == '.' && tmp[2] == '\0')
	{
		free(tmp);
		ft_error(127, W_POINT_POINT);
		return (FALSE);
	}
	free(tmp);
	return (TRUE);
}

static void	msg_syntax_error(char c, int n)
{
	char	*tmp;

	tmp = ft_strjoin("Minishell: syntax error near unexpected token `", &c);
	if (n == 2)
		tmp = free_strjoin(tmp, &c);
	tmp = free_strjoin(tmp, "\'\n");
	ft_error(2, tmp);
	free(tmp);
}

static int	verify_car(char *line, char c)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == c && line[i + 1] == c)
			return (msg_syntax_error(c, 2), FALSE);
		if (line[i] == c && line[i + 1] != c)
			return (msg_syntax_error(c, 1), FALSE);
	}
	return (TRUE);
}

void	verify_pipes(t_bigshell *data, int counter, int i)
{
	t_line	*tmp;
	int		redir_nb;

	if (!data || !data->line)
		return ;
	redir_nb = 0;
	tmp = data->line;
	while (tmp)
	{
		if (tmp->c == '<' || tmp->c == '>')
			redir_nb++;
		if (tmp->c == '|' && (redir_nb == 0 || redir_nb > 0))
		{
			if (i == 0 || counter == i - 1)
			{
				ft_free_line(&data->line);
				ft_error(2, W_PIPE);
				break ;
			}
			counter = i;
		}
		if (tmp->type != BLANK && tmp->type != LESS && tmp->type != GREAT)
			i++;
		tmp = tmp->next;
	}
}

int	verify_caracter(t_bigshell *data, char *line)
{
	verify_pipes(data, 0, 0);
	if (verify_car(line, '&') == FALSE || verify_car(line, ';') == FALSE)
		return (FALSE);
	if (verify_point(line) == FALSE)
		return (FALSE);
	return (TRUE);
}
