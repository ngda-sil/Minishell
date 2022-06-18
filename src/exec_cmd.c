/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:10:52 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/18 20:40:50 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (1);
	return (0);
}

void	exec_builtins(t_data *a, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		echo_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "cd"))
		cd_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		echo_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "export"))
		echo_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "unset"))
		echo_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "env"))
		echo_builtin(a, cmd->args);
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
		if (is_builtin(cmd))
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
