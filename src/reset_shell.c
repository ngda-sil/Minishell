/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/16 14:14:18 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_shell(t_data *a, char **env)
{
	free_all(a);
	a->env = env_into_list(env);
	rl_replace_line("", 0);
	a->prompt = get_prompt();
}
