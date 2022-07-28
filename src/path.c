/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:51:18 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/27 22:10:39 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(t_data *a, char *path)
{
	(void)a;
	if (access(path, F_OK) != 0)
		return (0);
	return (1);
}

char	**get_dirs(t_data *a)
{
	char	*env_path;
	char	**dirs;
	char	*tmp;
	int		i;

	env_path = ft_getenv(a->env, "PATH");
	dirs = ft_split(env_path, ':');
	i = 0;
	while (dirs[i] != NULL)
	{
		tmp = dirs[i];
		dirs[i] = ft_strjoin(dirs[i], "/");
		free(tmp);
		i++;
	}
	return (dirs);
}

char	*get_path(t_data *a, t_cmd *cmd)
{
	char	**dirs;
	char	*path;
	int		i;

	dirs = get_dirs(a);
	i = 0;
	while (dirs[i] != NULL)
	{
		path = ft_strjoin(dirs[i], cmd->args[0]);
		if (check_path(a, path))
		{
			ft_double_free(dirs);
			return (path);
		}
		free(path);
		i++;
	}
	ft_double_free(dirs);
	return (NULL);
}

void	tolower_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
}

void	check_first_arg(t_data *a, t_cmd *cmd)
{
	while (cmd)
	{
		tolower_str(cmd->args[0]);
		if (ft_strchr(cmd->args[0], '/'))
			cmd->path = ft_strdup(cmd->args[0]);
		else
			cmd->path = get_path(a, cmd);
		cmd = cmd->next;
	}
}
