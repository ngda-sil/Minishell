/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:02:34 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/09/11 18:54:47 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_status = 1;
	}
}

void	read_til_limiter(char *limiter, int p_write, int p_read)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	limiter = ft_strjoin(limiter, "\n");
	close(p_read);
	ft_putstr_fd("> ", 1);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter) + 1) == 0)
		{
			close(p_write);
			free(line);
			free(limiter);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, p_write);
		free(line);
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
	}
}

int	handle_heredoc(char *limiter)
{
	int	pid;
	int	wstatus;
	int	fd[2];

	if (pipe(fd) == -1)
		panic("minishell: pipe failed");
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		panic("minishell: fork failed");
	if (pid == 0)
		read_til_limiter(limiter, fd[1], fd[0]);
	else
	{
		signal(SIGINT, heredoc_handler);
		close(fd[1]);
		wait(&wstatus);
		if (WIFSIGNALED(wstatus))
		{
			return (-2);
		}
	}
	return (fd[0]);
}

t_list	*parse_heredoc(t_cmd *cmd, t_list *lst, int *check)
{
	if (!lst->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		g_status = 258;
		*check = 1;
		return (lst);
	}
	if (check_file_redirection(lst->next->content, check))
		return (lst);
	cmd->infile = handle_heredoc(lst->next->content);
	if (cmd->infile == -1)
		panic("minishell: heredoc failed");
	if (cmd->infile == -2)
		*check = 1;
	return (delete_redirection(cmd, lst));
}
