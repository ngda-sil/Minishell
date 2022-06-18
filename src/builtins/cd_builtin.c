/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:30:02 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/18 21:05:24 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error_msg(void)
{
	if (errno == 2)
		ft_putstr_fd(": No such file or directory\n", 2);
	if (errno == 5)
		ft_putstr_fd(": Inputut/output error", 2);
	if (errno == 13)
		ft_putstr_fd(": Permission denied\n", 2);
	if (errno == 14)
		ft_putstr_fd(": Bad address\n", 2);
	if (errno == 20)
		ft_putstr_fd(": Not a directory\n", 2);
	if (errno == 62)
		ft_putstr_fd(": Too many levels of symbolic links\n", 2);
	if (errno == 63)
		ft_putstr_fd(": File name too long\n", 2);
}

void	cd_builtin(char **args)
{
	if (args[1])
	{
		if (chdir(args[1]))
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[1], 2);
			cd_error_msg();
		}
	}
	else
	{
		if (chdir(ft_getenv("HOME")))
			ft_putstr_fd("Problem with chdir going to $HOME\n", 2);
	}
}
