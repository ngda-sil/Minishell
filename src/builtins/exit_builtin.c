/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:18:49 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/16 21:02:51 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - '0');
	}
	return ((long long)(sign * res));
}

void	exit_builtin(t_data *a)
{
	long long		status;

	if (!a->args[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
	if (LLONG_MAX <= ft_atoll(a->args[1]) || LLONG_MIN >= ft_atoll(a->args[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(a->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (255);
	}
	if (!a->args[2])
	{
		status = ft_atoll(a->args[1]);
		{
			ft_putstr_fd("exit\n", 1);
			exit(status % 256);
		}
	}
	else
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}
