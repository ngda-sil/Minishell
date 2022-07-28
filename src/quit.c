/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:21:16 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/28 21:27:18 by amuhleth         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

void	goodbye(t_data *a)
{
	printf("exit\n");
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &a.origin);
	free_all(&a);
}
