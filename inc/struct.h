/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:05:01 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/18 14:53:22 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>				//open
# include <stdlib.h> 			//exit
# include <unistd.h> 			//access, dup, dup2, execve, fork, pipe, unlink
# include <assert.h>
# include <string.h>			//strerror
# include <stdint.h>
# include <limits.h> 			// INT_MIN (-2147483648) INT_MAX (2147483647)
# include <signal.h>			// signal
# include <sys/wait.h> 			//wait, waitpid
# include <sys/stat.h>			// TBD
# include <sys/types.h> 		//wait, waitpid
# include <sys/prctl.h>
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline

// # define PROMPT "$ "
# define PROMPT "🔥 "
# define TRUE 0
# define FALSE 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

typedef struct s_line
{
	int				index;
	int				type;
	int				dq;
	int				sq;
	int				quote_flag;
	char			c;
	struct s_line	*next;
}	t_line;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	int				to_export;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				idx;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_simple_cmd
{
	int					idx;
	char				*cmd;
	char				**cmd_arg;
	int					fd_in;
	int					fd_out;
	int					end[2];
	char				*in_file;
	char				*out_file;
	int					builtin;
	t_redir				*redir;
	struct s_simple_cmd	*next;
	struct s_simple_cmd	*prev;
}	t_simple_cmd;

typedef struct s_token
{
	int				index;
	int				group;
	int				type;
	int				aim;
	int				quote_flag;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_bigshell
{
	int				fd_hd;
	char			**env_cpy;
	char			**env_paths;
	t_env			*env;
	t_line			*line;
	t_token			*token;
	t_simple_cmd	*simple_cmd;
}	t_bigshell;

#endif