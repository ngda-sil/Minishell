/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:13:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/28 19:54:44 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quotes_data(t_data *a, int i, char type)
{
	t_quotes	tmp;

	tmp.type = type;
	tmp.start = i;
	a->line[i] = '\0';
	i++;
	tmp.p = a->line + i;
	while (a->line[i] != type && a->line[i])
		i++;
	if (!a->line[i])
	{
		red_flag("minishell: syntax error near unexpected token 'quote'");
		g_status = 258;
		return (-1);
	}
	if (a->line[i] == type)
	{
		tmp.stop = i;
		a->line[i] = '\0';
	}
	lstadd_back_quotes(&a->quotes, lstnew_quotes(&tmp));
	return (i + 1);
}

char	is_inside_quotes(t_data *a, int i)
{
	t_quotes	*p;

	p = a->quotes;
	while (p)
	{
		if (p->start <= i && i <= p->stop)
			return (p->type);
		p = p->next;
	}
	return (0);
}

int	parse_quotes(t_data *a)
{
	int	i;

	i = 0;
	while (i < a->len)
	{
		if (a->line[i] == '\'')
			i = get_quotes_data(a, i, '\'');
		else if (a->line[i] == '\"')
			i = get_quotes_data(a, i, '\"');
		else
			i++;
		if (i == -1)
			return (1);
	}
	return (0);
}
