/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:32:52 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/18 16:16:20 by ngda-sil         ###   ########.fr       */
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
}

void	set_flag_echoctl(t_data *a)
{
	tcgetattr(STDIN_FILENO, &a->term);
	a->term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, 0, &a->term);
}

void	init_signals(t_data *a)
{
	set_flag_echoctl(a);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
