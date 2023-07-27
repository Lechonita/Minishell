/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:35:18 by Bea               #+#    #+#             */
/*   Updated: 2023/07/27 16:50:24 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* DOLLAR ADD VALUE */
t_line *line_new_var(t_line *line, t_line *after, char c, int index);
t_line	*line_add_node(t_line *line, char value, int index);
t_line *line_replace_node(t_line *line, char value);
void	add_var(t_line *line, char *value, int idx, char *var);

/* DOLLAR EXPANSION */
void    rm_var_excess(t_line *line, int index, char *var);
void	var_not_found(t_line **line, char *var);
void	compare_var(t_bigshell *data, t_line *line, char *var, int index);
void	rm_dollar(t_line *line);
void	dollar_expand(t_bigshell *data, t_line *line, char *var, int index);

/* DOLLAR UTILS */
void	align_line_index(t_line *line, int start);
int		get_var_len(t_line *line);
char	*get_var_bis(t_line *line, char *var);
char	*get_var(t_line *line);

/* DOLLAR */
void	do_expansion(t_bigshell *data, t_line *line, int index);
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