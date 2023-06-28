/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/28 16:23:38 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "error.h"
# include "token.h"

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
# include <termios.h>			//configuration terminal
# include <term.h>				//terminal capabilities
# include <curses.h>			//terminal capabilities

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# define TYPE_SEPARATOR 1		// ( ) { }
# define TYPE_OPERATOR 2		// & | < >
# define TYPE_WORD 3			// tous les autres caracteres
# define TYPE_INTEGER 4			// 0, 1 ,2 ...
# define TYPE_DOUBLE_QUOTES 5	// ""
# define TYPE_SINGLE_QUOTES 6	// ''
# define TYPE_BLANK 7			// space and \t
# define TYPE_DOLLAR 8			// $

typedef struct s_exec
{
	int				index;
	int				fd_in;
	int				fd_out;
	int				nb_cmd;
	char			*in_file;
	char			*out_file;
	int				fd[FOPEN_MAX][2];
	char			*cmd;
	char			**args;
	struct s_exec	*next;
}	t_exec;

typedef struct s_env
{
	char			*name;
	char			*value;
	char			**env_split;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	int				index;
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_line
{
	int				index;
	int				type;
	int				dq;
	int				sq;
	char			c;
	struct s_line	*next;
}	t_line;

typedef struct s_bigshell
{
	char			**history;
	t_env			*env;
	t_line			*line;
	t_token			*token;
	t_exec			*exec;
}	t_bigshell;

/***********************************************************/
/*                          MAIN                           */
/***********************************************************/

/* MAIN */
void	ft_readline(t_bigshell *data);

/***********************************************************/
/*                           ENV                           */
/***********************************************************/

/*  ENV INIT */
char	*get_env_name(char	*env);
void	init_env(t_bigshell *data, char **env);

/* SEARCH GOOD PATH */
void	get_path(t_bigshell *data);
char	*find_path_to_cmd(t_bigshell *data, char *cmd);

/***********************************************************/
/*                         SIGNAL                          */
/***********************************************************/

/* SIGNAL HANDLING */
void	catch_ctrl_d(t_bigshell *data, char *input);
void	ft_sig_int(int sig);
void	set_signal(void);

/***********************************************************/
/*                  	   TERMINAL	                       */
/***********************************************************/

/* Test only */
void	save_line_for_test(t_bigshell *data, char *input, int count);

/* TERMINAL CAPABILITIES */
int		init_term(void);
int		ft_termcap(t_bigshell *data);

/* REDIRECTION */
void	handle_here_doc(t_bigshell *data, char *limiter);
void	redirection_append(t_bigshell *data);
void	redirection_left(t_bigshell *data);
void	redirection_right(t_bigshell *data);
void	redirection(t_bigshell *data);

/***********************************************************/
/*                  	   PIPEX	                       */
/***********************************************************/

void	open_pipe(t_bigshell *data);
void	close_pipe(t_bigshell *data);
void	handle_dup(t_bigshell *data, int pcss);
pid_t	execute_pipex(t_bigshell *data, char *env[], int pcss);
int		ft_waitpid(pid_t last_pid);

/***********************************************************/
/*                          PARSER                         */
/***********************************************************/

/* LINE INIT */
t_line		*line_last(t_line	*line);
void		line_addback(t_line *line, t_line *new);
t_line		*line_new(t_line *line, char c, int i);
void		init_line(t_bigshell *data, char *line);

/* TYPE */
int			ft_is_integer(char c);
int			ft_is_word(char c);
int			ft_is_operator(char c);
int			ft_is_separator(char c);
int			ft_determine_type(char c);

/* TYPE2 */
int			ft_is_dollar(char c);
int			ft_is_blank(char c);
int			ft_is_single_quote(char c);
int			ft_is_double_quote(char c);

/* FIND QUOTES */
int			find_closing_quote(t_line *line, int type);
void		convert_quotes(t_line *line, int type);
void		find_quotes(t_line *line);
void		flag_double_quotes(t_line *line);
void		flag_single_quotes(t_line *line);

/***********************************************************/
/*                          LEXER                          */
/***********************************************************/

/* FIND TOKENS */
t_token	*token_last(t_token	*token);
void	token_addback(t_token *token, t_token *new);
t_token	*token_new(t_line *first, t_line *current, int start);
void	ft_create_token(t_bigshell *data, t_line *current, int start);
void	find_tokens(t_bigshell *data);

/***********************************************************/
/*                        EXPANDER                         */
/***********************************************************/

/* DOLLAR */

/* QUOTES FIND */
int			find_closing_quote(t_line *line, int type);
void		convert_quotes(t_line *line, int type);
void		find_quotes(t_line *line);

/* QUOTES OPEN */
void		delete_additional_quotes(t_line *line, int type);
void		assign_type_open_quotes(t_line *line);
int			determine_stop(t_line *line, int type);
void		input_open_quotes(t_line *line, char *input, int type);
void		get_rest_open_quotes(t_line *line, int type, char *prompt);
void		interpret_open_quotes(t_line *line, int type);

/* QUOTES POSITION */
// int			find_end_dq(t_line *line);
// int			find_start_dq(t_line *line);
// int			find_end_sq(t_line *line);
// int			find_start_sq(t_line *line);

/***********************************************************/
/*                  	  BUILTINS	                       */
/***********************************************************/

void    env(t_bigshell *data);
void	pwd(void);

/***********************************************************/
/*                          UTILS                          */
/***********************************************************/

/* FREE STRUCT*/
// void		ft_free_line_node(t_line *line);
void	ft_free_env(t_env **env);
void	ft_free_token(t_bigshell *data);
void	ft_free_history(t_bigshell *data);
void	ft_free_all(t_bigshell *data);

/* PRINT ERROR */
void	ft_exit(int err_no, char *msg);
void	error_execve(t_bigshell *data);
void	msg_not_found(char *msg, char *str);
void	error_not_found(t_bigshell *data, char *msg, char *str);

/* PRINT FUNCTION */
void	print_strs(char **strs);
void	print_t_line(t_bigshell *data);
void	print_t_token(t_bigshell *data);
void	display_env_struct(t_bigshell *data);
void	print_history_lst(t_bigshell *data);
#endif
