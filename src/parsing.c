/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:07:05 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/15 15:32:45 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_data *a, char *buffer)
{
	t_cmd	*p;

	p = lstlast_cmd(a->cmd);
	ft_lstadd_back(&a->cmd->tokens, ft_lstnew(buffer));
}

void	tokenization(t_data *a)
{
	int		i;
	char	*buffer;

	buffer = NULL;
	lstadd_back_cmd(&a->cmd, lstnew_cmd());
	i = 0;
	while (i < a->len)
	{
		while (ft_isspace(a->line[i]) && !is_inside_quotes(a, i))
			i++;
		if (a->line[i] == '|')
			parse_pipe(a);
		else if (a->line[i] == '<' || a->line[i] == '>')
			parse_redirection(a);
		else if (a->line[i] == '\0' && is_dollar(a, i))
			i = parse_dollar_token(a, i);
		else
			parse_args(a, buffer, i);
		i++;
	}
}

void	parsing(t_data *a)
{
	a->len = ft_strlen(a->line);
	parse_quotes(a);
	parse_dollar(a);
	tokenization(a);
	//print_quotes_list(a->quotes);
}
