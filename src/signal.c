/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:32:52 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/29 13:28:34 by ngda-sil         ###   ########.fr       */
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
	if (sig == SIGINT)
		g_status = 130;
	else if (sig == SIGQUIT)
	{
		printf("Quit: 3");
		g_status = 131;
	}
	printf("\n");
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
