/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:21:55 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/20 18:37:11 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	if (in != 0)
		close(in);
	if (out != 1)
		close(out);
}

void	set_pipe(t_cmd *cmd, int first)
{
	cmd->out = 1;
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
	printf("in:%d, out:%d\n", cmd->in, cmd->out);
}
