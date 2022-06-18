/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:11:30 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/18 16:28:09 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int	is_empty_quotes(t_data *a, int i)
{
	t_quotes	*p;

	p = a->quotes;
	while (p)
	{
		if (i == p->start && i + 1 == p->stop)
			return (1);
		p = p->next;
	}
	return (0);
}

// c'est pas fini

int	is_special_char(t_data *a, int i)
{
	char	c;

	c = a->line[i];
	if ((c == '|' || c == '<' || c == '>') && !is_inside_quotes(a, i))
		return (1);
	else if (ft_isspace(c) && !is_inside_quotes(a, i))
		return (1);
	else if (c == '\0' && is_empty_quotes(a, i))
		return (1);
	else if (a->len == i)
		return (1);
	else
		return (0);
}

char	*join_clean(char *s, char c)
{
	char	*res;
	int		i;
	int		len;

	if (s == NULL)
	{
		res = ft_calloc(2, sizeof(char));
		if (!res)
			return (NULL);
		res[0] = c;
		return (res);
	}
	len = ft_strlen(s);
	res = ft_calloc(len + 2, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	free(s);
	return (res);
}

char	*join_2(char *s1, char *s2)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);
}
