/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:35:18 by Bea               #+#    #+#             */
/*   Updated: 2023/07/06 14:35:09 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* DOLLAR */
int		get_var_len(t_line *line, int acolade);
char	*get_var(t_line *line);
t_line	*do_expansion(t_line *line);

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