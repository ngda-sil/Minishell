/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:25:12 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/29 19:41:30 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(t_data *a, int i)
{
	if (a->line[i] != '\0')
		a->buffer = join_clean(a->buffer, a->line[i]);
	if (is_special_char(a, i + 1) && a->buffer)
	{
		add_token(a, a->buffer);
		free(a->buffer);
		a->buffer = NULL;
	}
}

void	parse_pipe(t_data *a)
{
	lstadd_back_cmd(&a->cmd, lstnew_cmd());
}

t_quotes	*get_dollar(t_data *a, int i)
{
	t_quotes	*p;

	p = a->quotes;
	while (p)
	{
		if ((p->type == '$' || p->type == '?') && i == p->start)
			return (p);
		p = p->next;
	}
	return (NULL);
}

int	parse_dollar_token(t_data *a, int i)
{
	t_quotes	*p;

	p = get_dollar(a, i);
	if (p->p)
		a->buffer = join_2(a->buffer, p->p);
	if (is_special_char(a, p->stop + 1) && a->buffer)
	{
		add_token(a, a->buffer);
		free(a->buffer);
		a->buffer = NULL;
	}
	return (p->stop);
}

int	parse_redirection_token(t_data *a, int i)
{
	char	*tmp;

	if (a->line[i] == '<' && a->line[i + 1] == '<')
	{
		add_token(a, "<<");
		return (i + 1);
	}
	else if (a->line[i] == '>' && a->line[i + 1] == '>')
	{
		add_token(a, ">>");
		return (i + 1);
	}
	else
	{
		tmp = join_clean(NULL, a->line[i]);
		add_token(a, tmp);
		free(tmp);
	}
	return (i);
}
