/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:34:44 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/08 19:51:09 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char*	prompt(char **envp)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*user;
	int		i;

	i = ft_strlen(ft_strrchr(envp[21], '='));
	i--;
	temp = ft_strjoin(ft_substr(envp[21], i, i), "@");
	temp2 =	ft_strrchr(envp[7], '/');
	temp2++;
	temp3 = ft_strjoin(temp, temp2);
	user = ft_strjoin(temp3, ":~$ ");
	return (user);
}
