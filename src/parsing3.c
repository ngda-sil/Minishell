/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:46:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/29 16:21:26 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*delete_redirection(t_cmd *cmd, t_list *lst)
{
	t_list	*tmp;
	t_list	*ptr;

	if (lst == cmd->tokens)
	{
		cmd->tokens = lst->next->next;
		ft_lstdelone(lst->next, &free);
		ft_lstdelone(lst, &free);
		return (cmd->tokens);
	}
	else
	{
		ptr = cmd->tokens;
		while (ptr->next != lst)
			ptr = ptr->next;
		tmp = ptr->next->next->next;
		ft_lstdelone(ptr->next->next, &free);
		ft_lstdelone(ptr->next, &free);
		ptr->next = tmp;
		return (ptr->next);
	}
}

t_list	*parse_infile(t_cmd *cmd, t_list *lst, int *check)
{
	char	*file;

	if (!lst->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		g_status = 258;
		*check = 1;
		return (lst);
	}
	if (check_file_redirection(lst->next->content, check))
		return (lst);
	file = lst->next->content;
	cmd->infile = open(file, O_RDONLY);
	if (cmd->infile == -1)
	{
		red_flag("minishell: No such file or directory");
		g_status = 1;
		*check = 1;
		return (lst);
	}
	return (delete_redirection(cmd, lst));
}

t_list	*parse_outfile_trunc(t_cmd *cmd, t_list *lst, int *check)
{
	char	*file;

	if (!lst->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		g_status = 258;
		*check = 1;
		return (lst);
	}
	if (check_file_redirection(lst->next->content, check))
		return (lst);
	file = lst->next->content;
	cmd->outfile = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		panic("minishell: open failed");
	return (delete_redirection(cmd, lst));
}

t_list	*parse_outfile_append(t_cmd *cmd, t_list *lst, int *check)
{
	char	*file;

	if (!lst->next)
	{
		red_flag("minishell: syntax error near unexpected token 'newline'");
		g_status = 258;
		*check = 1;
		return (lst);
	}
	if (check_file_redirection(lst->next->content, check))
		return (lst);
	file = lst->next->content;
	cmd->outfile = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (cmd->outfile == -1)
		panic("minishell: open failed");
	return (delete_redirection(cmd, lst));
}

int	parse_redirections(t_cmd *cmd)
{
	t_list	*lst;
	int		check;

	check = 0;
	while (cmd)
	{
		lst = cmd->tokens;
		while (lst)
		{
			if (!ft_strncmp(lst->content, ">", 2))
				lst = parse_outfile_trunc(cmd, lst, &check);
			else if (!ft_strncmp(lst->content, ">>", 3))
				lst = parse_outfile_append(cmd, lst, &check);
			else if (!ft_strncmp(lst->content, "<", 2))
				lst = parse_infile(cmd, lst, &check);
			else if (!ft_strncmp(lst->content, "<<", 3))
				lst = parse_heredoc(cmd, lst, &check);
			else
				lst = lst->next;
			if (check == 1)
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
