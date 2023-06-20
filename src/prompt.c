/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/20 15:55:46 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	ft_save_history(t_bigshell *data, char *line, int i)
// {
// 	size_t	len;

// 	len = ft_strlen(line);
// 	data->history[i] = ft_strndup(line, len - 1);
// 	if (!data->history[i])
// 		return ;
// }

// void	ft_read_line(t_bigshell *data)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	line = NULL;
// 	// printf("line\n");
// 	while (1)
// 	{
// 		write(1, "bigshell42> ", 12);
// 		line = get_next_line(0);
// 		// printf("line = %s\n", line);
// 		if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) - 1 == 4)
// 			break ;
// 		if (line)
// 		{
// 			// data->history[i] = remove_new_line(line);
// 			// init_token(data, data->history[i - 1]);
// 			init_token(data, line);
// 			// display_token_struct(data); // A retirer
// 			i++;
// 		}
// 		if (i == 50)
// 			i = 0;
// 		free(line);
// 	}
// 	free(line);
// }

// void	ft_read_line(t_bigshell *data)
// {
// 	char	*buf;

// 	buf = readline(">> ");
// 	while (buf != NULL)
// 	{
// 		if (buf[0] != '\0')
// 			add_history(buf);
// 		if (!ft_strncmp(buf, "exit", 4) && ft_strlen(buf) - 1 == 4)
// 			break ;
// 		printf("[%s]\n", buf);
// 		free(buf);
// 	}
// 	free(buf);
// }
