/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:49:57 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/21 04:49:23 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env

void	lstdelone_env(t_env *lst)
{
	if (lst->name)
		free(lst->name);
	if (lst->value)
		free(lst->value);
	free(lst);
}

void	lstclear_env(t_env **lst)
{
	t_env	*p;
	t_env	*tmp;

	p = *lst;
	while (p)
	{
		tmp = p->next;
		lstdelone_env(p);
		p = tmp;
	}
	*lst = NULL;
}

// t_quotes

void	lstdelone_quotes(t_quotes *lst)
{
	if (lst->type == '?' && lst->p)
		free(lst->p);
	free(lst);
}

void	lstclear_quotes(t_quotes **lst)
{
	t_quotes	*p;
	t_quotes	*tmp;

	p = *lst;
	while (p)
	{
		tmp = p->next;
		lstdelone_quotes(p);
		p = tmp;
	}
	*lst = NULL;
}
