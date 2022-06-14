/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:09:36 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/14 14:56:25 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(t_data *a)
{
	if (!ft_strcmp(a->arg[0], "echo")) // gerer majuscules et minuscules melangees
		echo_builtin(a);
	if (!ft_strcmp(a->arg[0], "pwd"))
		printf("%s\n", getenv("PWD")); // je devrais faire une fonction, mais je le ferai au moment de gerer le echo $?	
	if (!ft_strcmp(a->arg[0], "cd"))
		cd_builtin(a);
}

void	execution(t_data *a)
{
	is_builtin(a);
}
