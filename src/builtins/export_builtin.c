/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:46:36 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/28 13:38:10 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	swap_env(t_env **p1, t_env **p2)
{
	t_env	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	print_export(t_env **p)
{
	int	i;

	i = -1;
	while (p[++i])
	{
		if (p[i]->value)
			printf("declare -x %s=\"%s\"\n", p[i]->name, p[i]->value);
		else
			printf("declare -x %s\n", p[i]->name);
	}
}

void	sort_env_list(t_env *lst)
{
	int		i;
	int		j;
	t_env	**p;
	t_env	*temp_l;

	j = -1;
	i = env_lstsize(lst);
	temp_l = lst;
	p = ft_calloc(i, sizeof(t_env *) + 1);
	while (++j < i)
	{
		p[j] = temp_l;
		temp_l = temp_l->next;
	}
	while (i > 0)
	{
		j = -1;
		while (++j < i - 1)
			if (ft_strcmp(p[j]->name, p[j + 1]->name) > 0)
				swap_env(&p[j], &p[j + 1]);
		i--;
	}
	print_export(p);
	free(p);
}

void	export_builtin(t_data *a, char **args)
{
	int		i;

	i = 1;
	if (!args[i])
		sort_env_list(a->env);
	else
	{
		while (args[i])
		{
			if (check_arg_name(args[i]))
			{
				red_flag("minishell : not a valid identifier");
				break ;
			}
			if (!is_in_env(a->env, args[i]))
				replace_in_env(a->env, args[i]);
			else
				add_to_env(&a->env, args[i]);
			i++;
		}
	}
}
