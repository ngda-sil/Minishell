/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:19:15 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/18 20:54:06 by amuhleth         ###   ########.fr       */
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

typedef struct s_cmd
{
	t_list	*tokens;
	char	**args;
	char	*path;
	pid_t	pid;
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
	struct termios	term;
	int				last_ret;
}					t_data;

void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);
char		*get_prompt(void);

void		handler(int sig);
void		init_signals(t_data *a);

void		reset_shell(t_data *a, char **env);

void		execution(t_data *a, t_cmd *cmd, char **env);

// env_into_list.c

t_env		*lstlast_env(t_env *lst);
void		lstadd_back_env(t_env **lst, t_env *new);
t_env		*lstnew_env(char *line, int name_len);
t_env		*env_into_list(char **env);
char		*ft_getenv(t_env *lst, char *name);
void		print_env_list(t_env *lst);

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

void		parse_empty_quotes(t_data *a, int i);
int			parse_redirections(t_data *a, t_cmd *cmd);

// utils.c

int			ft_isspace(int c);
int			is_empty_quotes(t_data *a, int i);
int			is_special_char(t_data *a, int i);
char		*join_clean(char *s, char c);
char		*join_2(char *s1, char *s2);

// quit.c

void		panic(char *message);
void		red_flag(char *message);

// builtins
void		echo_builtin(char **args);
void		cd_builtin(t_data *a, char **args);
void		exit_builtin(t_data *a);
void		pwd_builtin(t_data *a, char **args);
void		env_builtin(t_data *a, char **args);
void		export_builtin(t_data *a, char **args);

// free.c

void		lstdelone_cmd(t_cmd *lst);
void		lstclear_cmd(t_cmd **lst);
void		free_all(t_data *a);

// free2.c

void		lst_delone_env(t_env *lst);
void		lstclear_env(t_env **lst);
void		lstdelone_quotes(t_quotes *lst);
void		lstclear_quotes(t_quotes **lst);

// path.c

void		check_first_arg(t_data *a, t_cmd *cmd);

#endif
