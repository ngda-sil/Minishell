/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:10:52 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/20 19:23:47 by amuhleth         ###   ########.fr       */
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
		echo_builtin(cmd->args);
	if (!ft_strcmp(cmd->args[0], "cd"))
		cd_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd_builtin(a);
	if (!ft_strcmp(cmd->args[0], "export"))
		export_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "unset"))
		echo_builtin(cmd->args);
	if (!ft_strcmp(cmd->args[0], "env"))
		env_builtin(a, cmd->args);
}

void	exec_cmd(t_data *a, t_cmd *cmd, char **env)
{
	int	status;

	cmd->pid = fork();
	if (cmd->pid < 0)
		panic("minishell: fork failed");
	if (cmd->pid == 0)
	{
		printf("in:%d, out:%d\n", cmd->in, cmd->out);
		redirect(cmd, cmd->in, cmd->out);
		execve(cmd->path, cmd->args, env);
		panic("minishell: execve failed");
	}
	else if (cmd->pid > 0)
		waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		a->last_ret = WEXITSTATUS(status);
}

void	execution(t_data *a, t_cmd *cmd, char **env)
{
	int	first;

	first = 1;
	while (cmd)
	{
		set_pipe(cmd, first);
		set_redirections(cmd);
		if (is_builtin(cmd))
			exec_builtins(a, cmd);
		else
			exec_cmd(a, cmd, env);
		cmd = cmd->next;
		first = 0;
	}
}
