/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:18:49 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/29 19:53:09 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_not_num(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

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
		res = res * 10 + (*str++ - '0');
	return ((long long)(sign * res));
}

void	exit_builtin(t_data *a, char **args)
{
	long long		status;

	if (!args[1])
	{
		goodbye(a, 0);
		exit(g_status);
	}
	if (is_not_num(args[1]) || LLONG_MAX < ft_atoll(args[1])
		|| LLONG_MIN > ft_atoll(args[1]))
	{
		red_flag(ft_strjoin4("exit\nminishell: exit : ", args[1], ": ",
				"numeric argument required"));
		goodbye(a, 1);
		exit(255);
	}
	if (!args[2])
	{
		status = ft_atoll(args[1]);
		goodbye(a, 0);
		exit(status % 256);
	}
	else
		red_flag("minishell: exit: too many arguments");
	g_status = 1;
}
