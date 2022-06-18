/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:37:46 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/17 19:45:41 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(t_data *a, int i)
{
	t_quotes	*p;

	p = a->quotes;
	while (p)
	{
		if ((p->type == '$' || p->type == '?') && i == p->start)
			return (1);
		p = p->next;
	}
	return (0);
}

int	is_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	dollar_last_return(t_data *a, int i)
{
	t_quotes	new;

	new.start = i - 1;
	new.type = '?';
	a->line[i - 1] = '\0';
	new.stop = i;
	new.p = ft_itoa(a->last_ret);
	if (!new.p)
		panic("minishell: malloc failed");
	lstadd_back_quotes(&a->quotes, lstnew_quotes(&new));
}

void	dollar_env(t_data *a, int i)
{
	t_quotes	new;
	char		*tmp;

	new.start = i - 1;
	new.type = '$';
	a->line[i - 1] = '\0';
	while (is_env_char(a->line[i]))
		i++;
	new.stop = i - 1;
	tmp = ft_substr(a->line + new.start + 1, 0, new.stop - new.start);
	if (!tmp)
		panic("minishell: malloc failed");
	new.p = getenv(tmp);
	free(tmp);
	lstadd_back_quotes(&a->quotes, lstnew_quotes(&new));
}

void	parse_dollar(t_data *a)
{
	int	i;

	i = 0;
	while (i < a->len)
	{
		if (a->line[i] == '$' && is_inside_quotes(a, i) != '\'')
		{
			i++;
			if (a->line[i] == '?')
				dollar_last_return(a, i);
			else if (is_env_char(a->line[i]))
				dollar_env(a, i);
		}
		i++;
	}
}
