/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/24 17:17:35 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_termios(t_data *a)
{
	tcgetattr(STDIN_FILENO, &a->origin);
	a->term = a->origin;
	a->term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, 0, &a->term);
}

void	reset_shell(t_data *a, char **env)
{
	static int	count;

	if (count == 0)
	{
		a->env = env_into_list(env);
		init_signals();
		set_termios(a);
		count++;
	}
	free_each_time(a);
	rl_replace_line("", 0);
	a->prompt = get_prompt(a);
}
