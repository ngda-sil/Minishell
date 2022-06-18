/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:29:04 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/17 19:09:12 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	*lstlast_quotes(t_quotes *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_quotes(t_quotes **lst, t_quotes *new)
{
	t_quotes	*last;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = lstlast_quotes(*lst);
		last->next = new;
	}
}

t_quotes	*lstnew_quotes(t_quotes *src)
{
	t_quotes	*new;

	new = ft_calloc(sizeof(t_quotes), 1);
	if (!new)
		return (NULL);
	new->start = src->start;
	new->stop = src->stop;
	new->type = src->type;
	new->p = src->p;
	new->next = NULL;
	return (new);
}

void	print_quotes_list(t_quotes *lst)
{
	while (lst)
	{
		printf("Start:%d, stop:%d, type:%c, str:%s\n", lst->start,
			lst->stop, lst->type, lst->p);
		lst = lst->next;
	}
}
