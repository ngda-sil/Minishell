/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:46:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/18 16:28:20 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_empty_quotes(t_data *a, int i)
{
	if (a->buffer == NULL && is_special_char(a, i + 1))
		add_token(a, ft_strdup(""));
}

int	parse_infile(t_data *a, t_list *lst)
{
	(void)a;
	if (!lst->next->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		a->last_ret = 258;
		return (1);
	}
	return (0);
}

int	parse_outfile_trunc(t_data *a, t_list *lst)
{
	(void)a;
	if (!lst->next->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		a->last_ret = 258;
		return (1);
	}
	return (0);
}

int	parse_outfile_append(t_data *a, t_list *lst)
{
	(void)a;
	if (!lst->next->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		a->last_ret = 258;
		return (1);
	}
	return (0);
}

int	parse_redirections(t_data *a, t_cmd *cmd)
{
	t_list	*lst;
	int		check;

	check = 0;
	while (cmd)
	{
		lst = cmd->tokens;
		while (lst && lst->next)
		{
			if (!ft_strncmp(lst->next->content, ">", 2))
				check = parse_outfile_trunc(a, lst);
			else if (!ft_strncmp(lst->next->content, ">>", 3))
				check = parse_outfile_append(a, lst);
			else if (!ft_strncmp(lst->next->content, "<", 2))
				check = parse_infile(a, lst);
			if (check == 1)
				return (1);
			lst = lst->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
