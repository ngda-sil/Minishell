/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:07:05 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/16 11:36:05 by ngda-sil         ###   ########.fr       */
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
		if (a->line[i] == '|' && !is_inside_quotes(a, i))
			parse_pipe(a);
		else if ((a->line[i] == '<' || a->line[i] == '>')
			&& !is_inside_quotes(a, i))
			add_token(a, join_clean(NULL, a->line[i]));
		else if (a->line[i] == '\0' && is_dollar(a, i))
			i = parse_dollar_token(a, i);
		else if (a->line[i] == '\0' && is_empty_quotes(a, i))
			add_token(a, ft_strdup(""));
		else
			parse_args(a, i);
		i++;
	}
}

void	parsing(t_data *a)
{
	a->len = ft_strlen(a->line);
	parse_quotes(a);
	parse_dollar(a);
	tokenization(a);
	//print_cmd_tokens(a->cmd);
	//print_quotes_list(a->quotes);
}
