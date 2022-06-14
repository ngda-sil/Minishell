/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:37:46 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/12 18:03:28 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_char(char c)
{
	return (ft_isalpha || c == '_');
}

void	parse_dollar(t_data *a)
{
	int	i;

	i = 0;
	while (a->line[i])
	{
		if (a->line[i] == '$' && is_in_quotes != '\'')
		{
			i++;
			if (a->line[i] == '?')
				dollar_last_return(a);
			else if (is_env_char(a->line[i]))
				dollar_env(a);
		}
		i++;
	}
}
