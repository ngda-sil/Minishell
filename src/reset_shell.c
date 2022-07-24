/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/21 20:20:26 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_shell(t_data *a, char **env)
{
	static int	count;

	if (count == 0)
	{
		a->env = env_into_list(env);
		count++;
	}
	//free_all(a);
	//free_each_time(a);
	rl_replace_line("", 0);
	a->prompt = get_prompt(a);
}
