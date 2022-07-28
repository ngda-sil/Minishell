/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:09:10 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/28 20:39:10 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_only_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

void	echo_builtin(char **args)
{	
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (args[1] && !is_only_n(args[1]))
	{
		n++;
		while (!is_only_n(args[i + 1]))
			i++;
	}
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	g_status = 0;
}
