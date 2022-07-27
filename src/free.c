/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:24:59 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/27 22:00:41 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstdelone_cmd(t_cmd *lst)
{
	if (lst->tokens)
		ft_lstclear(&lst->tokens, &free);
	if (lst->args)
		free(lst->args);
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
		lstclear_cmd(&a->cmd);
	if (a->quotes)
		lstclear_quotes(&a->quotes);
	if (a->env)
		lstclear_env(&a->env);
	if (a->line)
	{
		free(a->line);
		a->line = NULL;
	}
	if (a->buffer)
	{
		free(a->buffer);
		a->buffer = NULL;
	}
}

void	free_each_time(t_data *a)
{
	if (a->cmd)
		lstclear_cmd(&a->cmd);
	if (a->quotes)
		lstclear_quotes(&a->quotes);
	if (a->line)
	{
		free(a->line);
		a->line = NULL;
	}
	if (a->prompt)
	{
		free(a->prompt);
		a->prompt = NULL;
	}
}
