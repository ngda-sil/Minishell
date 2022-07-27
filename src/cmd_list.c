/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:49:51 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/27 18:30:07 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = lstlast_cmd(*lst);
		last->next = new;
	}
}

t_cmd	*lstnew_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->out = 1;
	return (new);
}

void	print_cmd_tokens(t_cmd *cmd)
{
	t_list	*lst;

	while (cmd)
	{
		printf("cmd:\n");
		lst = cmd->tokens;
		while (lst)
		{
			printf("\"%s\"\n", (char *)lst->content);
			lst = lst->next;
		}
		cmd = cmd->next;
	}
}

void	print_cmd_args(t_cmd *cmd)
{
	int		i;

	printf("--- Print cmd args ---\n");
	while (cmd)
	{
		printf("cmd:\n");
		i = 0;
		while (cmd->args[i])
		{
			printf("\"%s\" ", cmd->args[i]);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
}
