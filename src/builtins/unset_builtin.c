/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 03:43:43 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/27 20:03:45 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_builtin(t_data *a, char **args)
{
	t_env	*tmp;
	t_env	*previous;
	int		i;

	i = 0;
	while (args[++i])
	{
		previous = a->env;
		if (ft_strlen(previous->name) == ft_strlen(args[i]))
		{
			if (!ft_strncmp(previous->name, args[i], ft_strlen(previous->name)))
			{
				a->env = previous->next;
				lstdelone_env(previous);
				break ;
			}
		}
		tmp = previous->next;
		while (tmp)
		{
			if (ft_strlen(tmp->name) == ft_strlen(args[i]))
			{
				if (!ft_strncmp(tmp->name, args[i], ft_strlen(tmp->name)))
				{
					previous->next = tmp->next;
					lstdelone_env(tmp);
					break ;
				}
			}
			previous = tmp;
			tmp = tmp->next;
		}
	}
}
