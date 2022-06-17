/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:09:36 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/17 19:15:43 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmpmin_maj(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i] || s1[i] == s2[i] - 32))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	is_builtin(t_data *a)
{
	if (!ft_strcmpmin_maj(a->arg[0], "echo"))
		echo_builtin(a);
	if (!ft_strcmpmin_maj(a->arg[0], "pwd"))
		pwd_builtin(); 	
	if (!ft_strcmpmin_maj(a->arg[0], "cd"))
		cd_builtin(a);
	if (!ft_strcmpmin_maj(a->arg[0], "exit"))
		exit_builtin(a);
}

void	execution(t_data *a)
{
	is_builtin(a);
}
