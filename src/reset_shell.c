/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/15 16:14:22 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_shell(t_data *a) //vrmt temporaire pour tester
{
	free (a->prompt);
	//rl_clear_history();
	exit(1);
}

void	reset_shell(t_data *a, char **env)
{	
	ft_bzero(a, sizeof(t_data));
	//a->line = ft_calloc(sizeof(char), LINE_MAX);
	a->env = env_into_list(env);
	a->prompt = get_prompt();
}
