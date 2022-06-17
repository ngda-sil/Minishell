/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:24:59 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/17 18:54:57 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstdelone_cmd(t_cmd *lst)
{
	if (lst->tokens)
		ft_lstclear(&lst->tokens, &free);
	if (lst->args)
		ft_double_free(lst->args);
	if (lst->path)
		free(lst->path);
	free(lst);
}

void	lstclear_cmd(t_cmd **lst)
{
	t_cmd	*p;
	t_cmd	*tmp;

	p = *lst;
	while (p)
	{
		tmp = p->next;
		lstdelone_cmd(p);
		p = tmp;
	}
	*lst = NULL;
}

void	free_all(t_data *a)
{
	if (a->cmd)
		free_cmd(a);
	if (a->quotes)
		free_quotes(a);
	if (a->env)
		free_env(a);
	if (a->line)
	{
		free(a->line)
		a->line = NULL;
	}
	if (a->prompt)
	{
		free(a->prompt)
		a->prompt = NULL;
	}
	if (a->buffer)
	{
		free(a->buffer)
		a->buffer = NULL;
	}
}
