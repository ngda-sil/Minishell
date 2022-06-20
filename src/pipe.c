/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:21:55 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/20 19:27:08 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_cmd *cmd, int in, int out)
{
	(void)cmd;
	dup2(in, 0);
	dup2(out, 1);
	/*if (in != 0)
		close(in);
	if (out != 1)
		close(out);*/
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
