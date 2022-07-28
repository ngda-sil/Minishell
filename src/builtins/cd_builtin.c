/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:30:02 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/28 20:06:06 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_pwd(t_env *lst)
{
	char	*tmp;

	while (lst)
	{
		if (!strncmp(lst->name, "PWD", 3))
		{
			tmp = lst->value;
			lst->value = ft_strdup(getcwd(NULL, 42));
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
			free (tmp);
			free (old_pwd);
			break ;
		}
		lst = lst->next;
	}
}

void	cd_builtin(t_data *a, char **args)
{
	if (args[1])
	{
		if (!chdir(args[1]))
			pwd_oldpwd_swap(a->env);
		else
			red_flag(ft_strjoin4("minishell: cd : ", args[1],
					": ", strerror(errno)));
	}
	else
	{
		if (!chdir(ft_getenv(a->env, "HOME")))
			pwd_oldpwd_swap(a->env);
		else
			red_flag("Problem with chdir going to $HOME\n");
	}
}
