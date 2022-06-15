/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:07:05 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/14 12:37:12 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_data *a)
{
	a->len = ft_strlen(a->line);
	parse_quotes(a);
	//parse_dollar(a);
	print_quotes_list(a->quotes);
}
