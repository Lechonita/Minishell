/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:34:19 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/03 11:14:20 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

// Rajouter le ctrl + C

void	delete_additional_quotes(t_line *line, int type)
{
	t_line	*prev;

	if (!line)
		return ;
	prev = line;
	printf("My HEAD is %c\n", prev->c);
	while (line)
	{
		prev = line;
		if (line->type == type && line->next)
		{
			// ft_free_line_node(line);
			free(line);
			line = prev->next;
		}
		line = line->next;
	}
}

void	assign_type_open_quotes(t_line *line)
{
	if (!line)
		return ;
	if (line->c == 39)
		line->type = SQUOTE;
	else if (line->c == 34)
		line->type = DQUOTE;
	else
		line->type = WORD;
}

int	determine_stop(t_line *line, int type)
{
	static int		count;

	while (line)
	{
		if (line->type == type)
			count++;
		line = line->next;
	}
	return (count);
}

// void	ft_line_delete(t_line *prev, t_line *current, int type)
// {
// 	if (!prev || !current || !type)
// 		return ;
// 	if (current->next->type == type)
// 		prev->next = current->next;
// }

void	input_open_quotes(t_line *line, char *input, int type)
{
	int		i;

	if (!line || !input || !type)
		return ;
	i = -1;
	while (line->next)
		line = line->next;
	while (input[++i])
	{
		line_addback(line, line_new(line, input[i], -1));
		line = line->next;
		assign_type_open_quotes(line);
	}
}

void	get_rest_open_quotes(t_line *line, int type, char *prompt)
{
	char	*input;

	if (!line || !prompt)
		return ;
	while (1)
	{
		input = readline(prompt);
		if (input)
		{
			line_addback(line, line_new(line, '\n', -1));
			input_open_quotes(line->next, input, type);
		}
		free(input);
		if (determine_stop(line, type) % 2 == 1)
			break ;
	}
}

void	interpret_open_quotes(t_line *line, int type)
{
	char	*prompt;
	t_line	*tmp;

	if (!line || !type)
		return ;
	while (line)
	{
		tmp = line;
		line->type = WORD;
		line = line->next;
	}
	if (type == 5)
		prompt = "dquote> ";
	else
		prompt = "quote> ";
	get_rest_open_quotes(tmp, type, prompt);
	delete_additional_quotes(tmp, type);
}
