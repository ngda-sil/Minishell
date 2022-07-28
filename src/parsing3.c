/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:46:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/28 14:05:03 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_redirection(t_list *lst)
{
	t_list	*tmp;

	tmp = lst->next->next->next;
	ft_lstdelone(lst->next->next, &free);
	ft_lstdelone(lst->next, &free);
	lst->next = tmp;
}

int	parse_infile(t_data *a, t_cmd *cmd, t_list *lst)
{
	char	*file;

	if (!lst->next->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		a->last_ret = 258;
		return (1);
	}
	file = lst->next->next->content;
	cmd->infile = open(file, O_RDONLY);
	if (cmd->infile == -1)
	{
		red_flag("minishell: No such file or directory");
		a->last_ret = 1;
		return (1);
	}
	delete_redirection(lst);
	return (0);
}

int	parse_outfile_trunc(t_data *a, t_cmd *cmd, t_list *lst)
{
	char	*file;

	if (!lst->next->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		a->last_ret = 258;
		return (1);
	}
	file = lst->next->next->content;
	cmd->outfile = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		panic("minishell: open failed");
	delete_redirection(lst);
	return (0);
}

int	parse_outfile_append(t_data *a, t_cmd *cmd, t_list *lst)
{
	char	*file;

	(void)cmd;
	if (!lst->next->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		a->last_ret = 258;
		return (1);
	}
	file = lst->next->next->content;
	cmd->outfile = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (cmd->outfile == -1)
		panic("minishell: open failed");
	delete_redirection(lst);
	return (0);
}

int	parse_redirections(t_data *a, t_cmd *cmd)
{
	t_list	*lst;
	int		check;

	(void)a;
	check = 0;
	while (cmd)
	{
		lst = cmd->tokens;
		while (lst && lst->next)
		{
			if (!ft_strncmp(lst->next->content, ">", 2))
				check = parse_outfile_trunc(a, cmd, lst);
			else if (!ft_strncmp(lst->next->content, ">>", 3))
				check = parse_outfile_append(a, cmd, lst);
			else if (!ft_strncmp(lst->next->content, "<", 2))
				check = parse_infile(a, cmd, lst);
			else
				lst = lst->next;
			if (check == 1)
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
