/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:13:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/12 17:00:07 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quotes_data(t_data *a, int i, char type)
{
	t_quotes	tmp;

	tmp.type = type;
	tmp.start = i;
	i++;
	while (a->line[i] != type && a->line[i])
		i++;
	if (!a->line[i])
		exit(1);
	if (a->line[i] == type)
		tmp.stop = i;
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

void	parse_quotes(t_data *a)
{
	int	i;

	i = 0;
	while (a->line[i])
	{
		if (a->line[i] == '\'')
			i = get_quotes_data(a, i, '\'');
		else if (a->line[i] == '\"')
			i = get_quotes_data(a, i, '\"');
		else
			i++;
	}
}
