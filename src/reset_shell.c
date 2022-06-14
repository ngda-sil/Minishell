/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/14 14:56:03 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_shell(t_data *a) //vrmt temporaire pour tester
{
	free (a->prompt);
	//while (1);
	//rl_clear_history();
	exit(1);
}

void	reset_shell(t_data *a, char **env)
{
	ft_bzero(a, sizeof(t_data));
	a->env = env_into_list(env);
	printf("coucoucocucouuc\n");
	a->prompt = get_prompt(a);
}
