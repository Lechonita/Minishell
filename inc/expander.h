/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:35:18 by Bea               #+#    #+#             */
/*   Updated: 2023/07/05 15:16:46 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* DOLLAR */

/* QUOTES FIND */
int		find_closing_quote(t_line *line, int type);
void	convert_quotes(t_line *line, int type);
void	find_quotes(t_line *line);

/* QUOTES OPEN */
void	delete_additional_quotes(t_line *line, int type);
void	assign_type_open_quotes(t_line *line);
int		determine_stop(t_line *line, int type);
void	input_open_quotes(t_line *line, char *input, int type);
void	get_rest_open_quotes(t_line *line, int type, char *prompt);
void	interpret_open_quotes(t_line *line, int type);

#endif