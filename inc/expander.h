/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:35:18 by Bea               #+#    #+#             */
/*   Updated: 2023/09/13 10:56:51 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* DOLLAR ADD VALUE */
t_line	*line_new_var(t_line *line, t_line *after, char c, int index);
t_line	*line_add_node(t_line *line, char value, int index);
t_line	*line_replace_node(t_line *line, char value);
void	line_addmiddle(t_line *line, char c, int index);
t_line	*add_var(t_line *line, char *value, char *var);

/* DOLLAR EXPANSION */
void	remove_rest(t_line *line, int value, int var);
t_line	*line_rm_next(t_line *prev);
t_line	*find_prev(t_bigshell *data, int index);
t_line	*var_not_found(t_bigshell *data, t_line **line, char *var, int index);
t_line	*compare_var(t_bigshell *data, t_line *line, char *var, int index);

/* DOLLAR UTILS */
void	align_line_index(t_line *line, int start);
int		get_var_len(t_line *line);
char	*get_var_bis(t_line *line, char *var);
char	*get_var(t_line *line);

/* DOLLAR */
void	find_dollar_dollar_bill(t_bigshell *data, t_line *line);

/* QUOTES FIND */
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