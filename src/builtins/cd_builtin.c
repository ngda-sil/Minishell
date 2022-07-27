/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:30:02 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/27 19:57:12 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_oldpwd_swap(t_env *lst)
{
	char	*tmp;
	t_env	*tmp_l;
	char	*old_pwd;

	tmp_l = lst;
	while (lst)
	{
		if (!ft_strncmp(lst->name, "PWD", 3))
		{
			tmp = lst->value;
			lst->value = ft_strdup(getcwd(NULL, 42));
			break ;
		}
		lst = lst->next;
	}
	while (tmp_l)
	{
		if (!ft_strncmp(tmp_l->name, "OLDPWD", 6))
		{
			old_pwd = tmp_l->value;
			tmp_l->value = ft_strdup(tmp);
			free (tmp);
			free (old_pwd);
			break ;
		}
		tmp_l = tmp_l->next;
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
