/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:05:01 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/25 16:52:36 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "minishell.h"

# include <stdio.h>
# include <stdlib.h> 			//exit
# include <unistd.h> 			//access, dup, dup2, execve, fork, pipe, unlink
# include <sys/types.h> 		//wait, waitpid
# include <sys/wait.h> 			//wait, waitpid
# include <errno.h>
# include <string.h>			//strerror
# include <fcntl.h>				//open
# include <stdint.h>
# include <limits.h> 			// INT_MIN (-2147483648) INT_MAX (2147483647)
# include <signal.h>			// signal
# include <sys/stat.h>			// TBD
# include <assert.h>
# include <sys/prctl.h>
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline

# define PROMPT "$ "
// # define PROMPT "🔥 "
# define TRUE 1
# define FALSE 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

typedef struct s_line
{
	int				index;
	int				type;
	int				dq;
	int				sq;
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

typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_arg;
	int				fd_in;
	int				fd_out;
	char			*in_file;
	char			*out_file;
	int				idx_cmd;
	int				builtin;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				idx;
	int				fd;
	int				with_cmd_nb;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	int				nb_cmd;
	char			*in_file;
	char			*out_file;
	int				fd[FOPEN_MAX][2];
	int				here_doc;
	t_cmd			*cmd;
}	t_exec;

typedef struct s_token
{
	int				index;
	int				type;
	int				aim;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_bigshell
{
	char			**env_paths;
	int				redir_or_not;
	t_env			*env;
	t_line			*line;
	t_token			*token;
	t_redir			*in_out;
	t_exec			*exec;
}	t_bigshell;


#endif