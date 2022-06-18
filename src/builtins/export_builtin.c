/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:46:36 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/17 21:09:06 by ngda-sil         ###   ########.fr       */
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

void	sort_env_list(t_env *lst)
{
	int		i;
	int		j;
	t_env	**p;
	t_env	*temp_l;

	j = -1;
	i = env_lstsize(lst);
	temp_l = lst;
	p = ft_calloc(i, sizeof(t_env *));
	while (++j < i)
	{
		p[j] = temp_l;
		temp_l = temp_l->next;
	}
	while (--i > 0)
	{
		j = -1;
		while (++j < i - 2)
			if (ft_strcmp(p[j]->name, p[j + 1]->name) > 0)
				swap_env(&p[j], &p[j + 1]);
	}
	j = -1;
	while (p[++j])
		printf("declare -x %s=\"%s\"\n", p[j]->name, p[j]->value);
	free(p);
}

void	export_builtin(t_data *a)
{
	if (!a->args[1])
		sort_env_list(a->env);
	// 1 checker si le name existe ?
	// 	1.1 si oui -> ecraser valeur env.
	// 	1.2 si non -> ajouter a la liste new;
	// 2 si plusieurs arg le meme ecraser le premier par le deuxieme
	// 3 checker si xxx=xxxx -> faux export apparait pas dans env mais apparait dans export SA
	// a faire list new;
}
