/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:32:52 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/08 23:13:18 by ngda-sil         ###   ########.fr       */
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
	}
	if (sig == SIGSEGV) //pas du tout gere comme dans bash - solution temp
	{
		printf("exit");
		exit(0);
	}
}

void	set_flag_echoctl(void)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, 0, &termios_p);
}

void	init_signals(void)
{
	set_flag_echoctl();
	signal(SIGSEGV, handler);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
