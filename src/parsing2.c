/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:25:12 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/15 15:26:29 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirection(t_data *a)
{
}

void	parse_args(t_data *a, char *buffer, int i)
{
	if (a->line[i] != '\0')
		buffer = join_clean(buffer, a->line[i]);
	if (is_special_char(a, i + 1))
		add_token(a, buffer);
}

void	parse_pipe(t_data *a)
{
}

int	parse_dollar_token(t_data *a, int i)
{
	return (i);
}
