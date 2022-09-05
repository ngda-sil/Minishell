/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 03:43:43 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/09/05 18:02:58 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_first_elem(t_env *prev, char *arg, t_data *a)
{
	if (ft_strlen(prev->name) == ft_strlen(arg))
	{
		if (!ft_strncmp(prev->name, arg, ft_strlen(prev->name)))
		{
			a->env = prev->next;
			lstdelone_env(prev);
			return (1);
		}
	}
	return (0);
}

static int	check_all_elem(t_env *tmp, t_env *prev, char *arg)
{
	if (ft_strlen(tmp->name) == ft_strlen(arg))
	{
		if (!ft_strncmp(tmp->name, arg, ft_strlen(tmp->name)))
		{
			prev->next = tmp->next;
			lstdelone_env(tmp);
			return (1);
		}
	}
	return (0);
}

void	unset_builtin(t_data *a, char **args)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[++i] && a->env != NULL)
	{
		prev = a->env;
		if (check_first_elem(prev, args[i], a))
			continue ;
		tmp = prev->next;
		while (tmp)
		{
			if (check_all_elem(tmp, prev, args[i]))
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
	}
	g_status = 0;
}
