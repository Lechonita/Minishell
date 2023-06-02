/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/05/24 10:28:50 by bebigel          ###   ########.fr       */
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

typedef struct  s_bigshell
{
  char      *history[50];
  char      **argvs;
  t_env		*env;
}	t_bigshell;

typedef struct	s_env
{
	char		*name;
	char		*value;
	struct s_env	*next;
}				t_env;

#endif
