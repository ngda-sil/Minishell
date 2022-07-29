/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:10:52 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/29 13:34:49 by ngda-sil         ###   ########.fr       */
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
	if (!ft_strcmp(cmd->args[0], "exit"))
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
		unset_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "env"))
		env_builtin(a, cmd->args);
	if (!ft_strcmp(cmd->args[0], "exit"))
		exit_builtin(cmd->args);
}

void	exec_cmd(t_data *a, t_cmd *cmd, char **env)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &a->origin);
	signal(SIGINT, &child_handler);
	signal(SIGQUIT, &child_handler);
	cmd->pid = fork();
	if (cmd->pid < 0)
		panic("minishell: fork failed");
	if (cmd->pid == 0)
	{
		redirect(cmd, cmd->in, cmd->out);
		if (is_builtin(cmd))
		{
			exec_builtins(a, cmd);
			exit(g_status);
		}	
		execve(cmd->path, cmd->args, env);
		panic("minishell: execve failed");
	}
}

void	wait_for_child(t_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		cmd = cmd->next;
	}
}

void	execution(t_data *a, t_cmd *cmd, char **env)
{
	int		first;

	first = 1;
	if (!cmd->next && is_builtin(cmd))
		redirect_and_exec_builtins(a, cmd);
	else
	{
		while (cmd)
		{
			set_pipe(cmd, first);
			set_redirections(cmd);
			exec_cmd(a, cmd, env);
			cmd = cmd->next;
			first = 0;
		}
	}
	close_pipes(a->cmd);
	wait_for_child(a->cmd);
}
