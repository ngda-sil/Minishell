/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:19:15 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/09/05 18:06:44 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "../Libft/incl/libft.h"

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
typedef struct s_quotes	t_quotes;

extern int				g_status;
typedef struct s_cmd
{
	t_list	*tokens;
	char	**args;
	char	*path;
	pid_t	pid;
	int		in;
	int		out;
	int		infile;
	int		outfile;
	int		fd[2];
	t_cmd	*next;
}			t_cmd;

typedef struct s_quotes
{
	int			start;
	int			stop;
	char		type;
	char		*p;
	t_quotes	*next;
}				t_quotes;

typedef struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
}			t_env;

typedef struct s_data
{
	t_cmd			*cmd;
	t_quotes		*quotes;
	t_env			*env;
	char			*line;	
	char			*prompt;
	char			*buffer;
	int				len;
	struct termios	origin;
	struct termios	term;
}					t_data;

void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);
char		*get_prompt(t_data *a);

void		handler(int sig);
void		child_handler(int sig);
void		init_signals(void);

void		reset_shell(t_data *a, char **env);
void		set_termios(t_data *a);

// exec_cmd.c (execution)

void		execution(t_data *a, t_cmd *cmd, char **env);
void		exec_builtins(t_data *a, t_cmd *cmd);

// env_into_list.c

t_env		*lstlast_env(t_env *lst);
void		lstadd_back_env(t_env **lst, t_env *new);
t_env		*lstnew_env(char *line, int name_len, int sep);
t_env		*env_into_list(char **env);
char		*ft_getenv(t_env *lst, char *name);

// utils to t_quotes linked list -> quotes_list.c

t_quotes	*lstlast_quotes(t_quotes *lst);
void		lstadd_back_quotes(t_quotes **lst, t_quotes *new);
t_quotes	*lstnew_quotes(t_quotes *src);
void		print_quotes_list(t_quotes *lst);

// quotes.c

int			parse_quotes(t_data *a);
char		is_inside_quotes(t_data *a, int i);

// parse dollar to env    -> dollar.c

void		parse_dollar(t_data *a);
int			is_dollar(t_data *a, int i);

// prompt.c

char		*ft_strjoin4(char const *s1, char const *s2, char const *s3,
				char const *s4);

// utils to use t_cmd linked list ->cmd_list.c

t_cmd		*lstlast_cmd(t_cmd *lst);
void		lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd		*lstnew_cmd(void);
void		print_cmd_tokens(t_cmd *cmd);
void		print_cmd_args(t_cmd *cmd);

// parsing.c

int			parsing(t_data *a);
void		add_token(t_data *a, char *buffer);
void		tokenization(t_data *a);

// parsing2.c

void		parse_args(t_data *a, int i);
void		parse_pipe(t_data *a);
int			parse_dollar_token(t_data *a, int i);
int			parse_redirection_token(t_data *a, int i);

// parsing3.c

int			parse_redirections(t_cmd *cmd);
t_list		*delete_redirection(t_cmd *cmd, t_list *lst);

t_list		*parse_heredoc(t_cmd *cmd, t_list *lst, int *check);

// parsing4.c

void		parse_empty_quotes(t_data *a, int i);
int			check_cmd(t_cmd *cmd);
int			check_file_redirection(char *file, int *check);

// utils.c

int			ft_isspace(int c);
int			is_empty_quotes(t_data *a, int i);
int			is_special_char(t_data *a, int i);
char		*join_clean(char *s, char c);
char		*join_2(char *s1, char *s2);

// quit.c

void		panic(char *message);
void		red_flag(char *message);
void		goodbye(t_data *a, int do_not_print);
// builtins

void		echo_builtin(char **args);
void		cd_builtin(t_data *a, char **args);
void		exit_builtin(t_data *a, char **args);
void		pwd_builtin(void);
void		env_builtin(t_data *a, char **args);
void		export_builtin(t_data *a, char **args);
void		unset_builtin(t_data *a, char **args);

// export utils

void		add_to_env(t_env **lst, char *arg);
int			is_in_env(t_env *lst, char *arg);
int			check_arg_name(char *arg);
void		replace_in_env(t_env *lst, char *arg);

// free.c

void		lstdelone_cmd(t_cmd *lst);
void		lstclear_cmd(t_cmd **lst);
void		free_all(t_data *a);
void		free_each_time(t_data *a);

// free2.c

void		lstdelone_env(t_env *lst);
void		lstclear_env(t_env **lst);
void		lstdelone_quotes(t_quotes *lst);
void		lstclear_quotes(t_quotes **lst);

// path.c

void		check_first_arg(t_data *a, t_cmd *cmd);

// pipe.c

void		set_pipe(t_cmd *cmd, int first);
void		set_redirections(t_cmd *cmd);
void		redirect(t_cmd *cmd, int in, int out);
void		redirect_and_exec_builtins(t_data *a, t_cmd *cmd);
void		close_pipes(t_cmd *cmd);

#endif
