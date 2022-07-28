/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:32:52 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/28 21:01:28 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	child_handler(int sig)
{
	(void)sig;
	printf("\n");
	g_status = 130;
}

void	set_flag_echoctl(t_data *a)
{
	tcgetattr(STDIN_FILENO, &a->term);
	a->term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, 0, &a->term);
}

void	init_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
