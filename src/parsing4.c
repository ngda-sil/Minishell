/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:05:12 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/27 20:19:58 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->args[0] == NULL)
		{
			red_flag("minishell: syntax error near unexpected token 'pipe'");
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
