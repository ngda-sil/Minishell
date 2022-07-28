/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:53:54 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/28 20:58:41 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_list(t_env *lst)
{
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
}

void	env_builtin(t_data *a, char **args)
{
	if (!args[1])
	{
		print_env_list(a->env);
		g_status = 0;
	}
	else
	{
		red_flag("Pas d'argument, on n'est pas des bashelorettes, cf p.5");
		g_status = 1;
	}
}
