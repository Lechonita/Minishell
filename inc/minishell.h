/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/06 17:29:47 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h>
# include <stdlib.h> 	//exit
# include <unistd.h> 	//access, dup, dup2, execve, fork, pipe, unlink
# include <sys/types.h> //wait, waitpid
# include <sys/wait.h> 	//wait, waitpid
# include <errno.h>
# include <string.h>	//strerror
# include <fcntl.h>		//open
# include <stdint.h>
# include <limits.h> 	// INT_MIN (-2147483648) INT_MAX (2147483647)

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_bigshell
{
	char			*history[50];
	char			**argv;
	t_env			*env;
}	t_bigshell;

/* INIT ENV */
t_env	*env_last(t_env *new);
void	env_addback(t_env *new, t_env *env);
t_env	*env_new(char *env);
char	*ft_strndup(const char *src, size_t n);
char	*get_value(char *env);
int		find_equal(char *env);
char	*get_name(char	*env);
void	init_env(t_bigshell *data, char **env);
// void	display_env_struct(t_bigshell *data);

// void	init_argv(t_bigshell *data, int ac, char *av[]);

#endif
