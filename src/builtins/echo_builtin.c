/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:09:10 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/15 16:26:16 by ngda-sil         ###   ########.fr       */
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

void	echo_builtin(t_data *a)
{
	int	i;
	int n;

	i = 0;
	n = 0;
	if (a->arg[1] && !is_only_n(a->arg[1]))
	{
		n++;
		i++;
	}
	while (a->arg[++i])
		printf("%s ", a->arg[i]);
	if (!n)
		printf("\n");
}
