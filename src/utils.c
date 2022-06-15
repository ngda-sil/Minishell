/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:11:30 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/15 14:43:22 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int	is_special_char(t_data *a, int i)
{
	char	c;

	c = a->line[i];
	if (c == '|' || c == '<' || c == '>')
		return (1);
	if (ft_isspace(c) && !is_inside_quotes(a, i))
		return (1);
	if (c == '\0' && is_dollar(a, i))
		return (0);
}
