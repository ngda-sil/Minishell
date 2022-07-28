
#include "minishell.h"

void	read_til_limiter(char *limiter, int p_write, int p_read)
{
	char	*line;

	limiter = ft_strjoin(limiter, "\n");
	close(p_read);
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
		line = get_next_line(STDIN_FILENO);
	}
}

int	handle_heredoc(char *limiter)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		panic("minishell: pipe failed");
	pid = fork();
	if (pid < 0)
		panic("minishell: fork failed");
	if (pid == 0)
		read_til_limiter(limiter, fd[1], fd[0]);
	else
	{
		close(fd[1]);
		wait(NULL);
	}
	return (fd[0]);
}

t_list	*parse_heredoc(t_data *a, t_cmd *cmd, t_list *lst, int *check)
{
	if (!lst->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		a->last_ret = 258;
		*check = 1;
		return (lst);
	}
	cmd->infile = handle_heredoc(lst->next->content);
	if (cmd->infile == -1)
		panic("minishell: heredoc failed");
	return (delete_redirection(cmd, lst));
}
