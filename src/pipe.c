/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:21:55 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/29 16:30:03 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_cmd *cmd, int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	if (in != 0 && in != 1)
		close(in);
	if (out != 0 && out != 1)
		close(out);
	close_pipes(cmd);
}

void	redirect_and_exec_builtins(t_data *a, t_cmd *cmd)
{
	int	stdi;
	int	stdo;

	set_redirections(cmd);
	stdi = dup(STDIN_FILENO);
	stdo = dup(STDOUT_FILENO);
	redirect(a->cmd, cmd->in, cmd->out);
	exec_builtins(a, cmd);
	redirect(a->cmd, stdi, stdo);
}

void	set_pipe(t_cmd *cmd, int first)
{
	if (!first)
	{
		cmd->in = cmd->fd[0];
		close(cmd->fd[1]);
	}
	if (cmd->next)
	{
		pipe(cmd->next->fd);
		cmd->out = cmd->next->fd[1];
	}
}

void	set_redirections(t_cmd *cmd)
{
	if (cmd->infile)
	{
		if (cmd->in != 0)
			close(cmd->in);
		cmd->in = cmd->infile;
	}
	if (cmd->outfile)
	{
		if (cmd->out != 1)
			close(cmd->out);
		cmd->out = cmd->outfile;
	}
}

void	close_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd[0] != 1 && cmd->fd[0] != 0 && cmd->fd[0] != 2)
			close(cmd->fd[0]);
		if (cmd->fd[1] != 1 && cmd->fd[1] != 0 && cmd->fd[1] != 2)
			close(cmd->fd[1]);
		cmd = cmd->next;
	}
}
