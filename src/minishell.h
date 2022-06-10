/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:19:15 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/10 17:56:59 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	char	*path;
	t_cmd	*next;
}			t_cmd;

typedef struct s_quotes
{
	int			start;
	int			stop;
	char		type;
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
	char			*line;
	char			*prompt;
	t_quotes		*quotes;
	t_env			*env;
	struct termios	term;
}					t_data;

void		rl_replace_line(const char *text, int clear_undo);

char		*prompt(char **envp);

void		handler(int sig, siginfo_t *info, void *context);

void		reset_shell(t_data *a, char **env);

void		parsing(t_data *a);

// env_into_list.c

t_env		*lstlast_env(t_env *lst);
void		lstadd_back_env(t_env **lst, t_env *new);
t_env		*lstnew_env(char *line, int name_len);
t_env		*env_into_list(char **env);

// utils to t_quotes linked list -> quotes_list.c

t_quotes	*lstlast_quotes(t_quotes *lst);
void		lstadd_back_quotes(t_quotes **lst, t_quotes *new);
t_quotes	*lstnew_quotes(t_quotes *src);

void		parse_quotes(t_data *a);

#endif
