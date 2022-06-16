/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:46:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/16 15:56:32 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(t_data *a, t_list *lst)
{
	(void)a;
	if (!lst->next)
		exit(1);
}

void	parse_output(t_data *a, t_list *lst)
{
	(void)a;
	if (!lst->next)
		exit(1);
}

void	parse_redirections(t_data *a, t_cmd *cmd)
{
	t_list	*lst;

	while (cmd)
	{
		lst = cmd->tokens;
		while (lst)
		{
			if (!ft_strncmp(lst->content, ">", 2))
				parse_output(a, lst);
			else if (!ft_strncmp(lst->content, "<", 2))
				parse_input(a, lst);
			lst = lst->next;
		}

		cmd = cmd->next;
	}
}
