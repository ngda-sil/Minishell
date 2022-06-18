/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:10:52 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/18 18:36:38 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_data *a, t_cmd *cmd)
{
	(void)a;
	(void)cmd;
	return (0);
}

void	exec_builtins(t_data *a, t_cmd *cmd)
{
	(void)a;
	(void)cmd;
}

void	exec_cmd(t_data *a, t_cmd *cmd, char **env)
{
	int	status;

	cmd->pid = fork();
	if (cmd->pid < 0)
		panic("minishell: fork failed");
	if (cmd->pid == 0)
	{
		//cmd->path = get_cmd_path(a, cmd);
		if (is_builtin(a, cmd))
			exec_builtins(a, cmd);
		execve(cmd->path, cmd->args, env);
		panic("minishell: execve failed");
	}
	else if (cmd->pid > 0)
		wait(&status);
	if (WIFEXITED(status))
		a->last_ret = WEXITSTATUS(status);
}

void	execution(t_data *a, t_cmd *cmd, char **env)
{
	while (cmd)
	{
		exec_cmd(a, cmd, env);
		cmd = cmd->next;
	}
}
