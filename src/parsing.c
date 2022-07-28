/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:07:05 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/28 21:22:38 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lstnew_dup(void *content)
{
	t_list	*new;

	new = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	return (new);
}

void	add_token(t_data *a, char *buffer)
{
	t_cmd	*p;

	p = lstlast_cmd(a->cmd);
	ft_lstadd_back(&p->tokens, lstnew_dup(buffer));
}

void	tokenization(t_data *a)
{
	int		i;

	lstadd_back_cmd(&a->cmd, lstnew_cmd());
	i = 0;
	while (i < a->len)
	{
		while (ft_isspace(a->line[i]) && !is_inside_quotes(a, i))
			i++;
		if (i >= a->len)
			break ;
		if (a->line[i] == '|' && !is_inside_quotes(a, i))
			parse_pipe(a);
		else if ((a->line[i] == '<' || a->line[i] == '>')
			&& !is_inside_quotes(a, i))
			i = parse_redirection_token(a, i);
		else if (a->line[i] == '\0' && is_dollar(a, i))
			i = parse_dollar_token(a, i);
		else if (a->line[i] == '\0' && is_empty_quotes(a, i))
			parse_empty_quotes(a, i);
		else
			parse_args(a, i);
		i++;
	}
}

void	tokens_to_args(t_cmd *cmd)
{
	t_list	*lst;
	int		nb_tokens;
	int		i;

	while (cmd)
	{
		nb_tokens = ft_lstsize(cmd->tokens);
		cmd->args = ft_calloc(nb_tokens + 1, sizeof(char *));
		if (!cmd->args)
			panic("minishell: malloc failed");
		lst = cmd->tokens;
		i = 0;
		while (lst)
		{
			cmd->args[i] = lst->content;
			i++;
			lst = lst->next;
		}
		cmd = cmd->next;
	}
}

int	parsing(t_data *a)
{
	a->len = ft_strlen(a->line);
	if (parse_quotes(a))
		return (1);
	parse_dollar(a);
	tokenization(a);
	if (parse_redirections(a->cmd))
		return (1);
	tokens_to_args(a->cmd);
	if (a->cmd->args[0] == NULL && a->cmd->next == NULL)
		return (1);
	else if (check_cmd(a->cmd))
		return (1);
	check_first_arg(a, a->cmd);
	return (0);
}
