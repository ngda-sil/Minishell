/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:30:02 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/09/05 18:51:44 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_pwd(t_env *lst)
{
	char	*tmp;

	while (lst)
	{
		if (!ft_strncmp(lst->name, "PWD", 3))
		{
			tmp = lst->value;
			lst->value = getcwd(NULL, 42);
			return (tmp);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	pwd_oldpwd_swap(t_env *lst)
{
	char	*tmp;
	char	*old_pwd;

	tmp = get_pwd(lst);
	while (lst)
	{
		if (!ft_strncmp(lst->name, "OLDPWD", 6))
		{
			old_pwd = lst->value;
			lst->value = ft_strdup(tmp);
			free(tmp);
			free(old_pwd);
			break ;
		}
		lst = lst->next;
	}
}

void	check_if_swap(t_env *lst)
{
	if (ft_getenv(lst, "PWD") != NULL)
		pwd_oldpwd_swap(lst);
}

void	cd_builtin(t_data *a, char **args)
{
	g_status = 0;
	if (args[1] && ft_strncmp(args[1], "~", 2))
	{
		if (!chdir(args[1]))
			check_if_swap(a->env);
		else
		{
			red_flag(ft_strjoin4("minishell: cd : ", args[1],
					": ", strerror(errno)));
			g_status = 1;
		}
	}
	else
	{
		if (!chdir(ft_getenv(a->env, "HOME")))
			check_if_swap(a->env);
		else
		{
			red_flag("Problem with chdir going to $HOME\n");
			g_status = 1;
		}
	}
}
