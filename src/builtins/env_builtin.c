/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:53:54 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/27 17:48:16 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_list2(t_env *lst)
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
		print_env_list2(a->env);
	else
		red_flag("Votre shell doit implémenter les builtins suivantes : env \
				SANS aucune option NI argument. cf sujet p.5");
}
