/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:21:16 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/29 19:54:22 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_flag(char *message)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd("\033[0m", 2);
}

void	panic(char *message)
{
	red_flag(message);
	exit(g_status);
}

void	goodbye(t_data *a, int do_not_print)
{
	if (!do_not_print)
		printf("exit\n");
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &a->origin);
	free_all(a);
}
