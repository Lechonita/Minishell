/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:34:19 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/23 13:22:54 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Rajouter le ctrl + C
// gerer plusieurs lignes

void	assign_type_open_quotes(t_line *line)
{
	if (!line)
		return ;
	if (line->c == 39)
		line->type = TYPE_SINGLE_QUOTES;
	else if (line->c == 34)
		line->type = TYPE_DOUBLE_QUOTES;
	else
		line->type = TYPE_WORD;
}

int	determine_stop(t_line *line, int type)
{
	int		count;

	count = 0;
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
	t_line	*tmp;

	if (!input || !line || !type)
		return ;
	i = -1;
	while (input[++i])
	{
		tmp = line;
		line_addback(line, line_new(line, input[i], -1));
		printf("et mon line current = %c\n", line->c);
		assign_type_open_quotes(line->next);
		printf("Mon line->next == %c\n", line->next->c);
		line = line->next;
		printf("input de i + 1 = -%c-\n", input[i + 1]);
		if (line->type == type && input[i + 1])
			// tmp->next = line->next; // delete node line
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
			input_open_quotes(line, input, type);
		free(input);
		if (determine_stop(line, type) % 2 != 0)
			break ;
	}
	printf("Apres le break, je passe quand meme ici\n");
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
		line->type = TYPE_WORD;
		line = line->next;
	}
	line_addback(tmp, line_new(tmp, '\n', -1));
	if (type == 5)
		prompt = "dquote> ";
	else
		prompt = "quote> ";
	get_rest_open_quotes(tmp, type, prompt);
}
