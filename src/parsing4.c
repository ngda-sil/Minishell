/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:05:12 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/07/28 20:00:49 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_empty_quotes(t_data *a, int i)
{
	if (is_special_char(a, i + 2))
	{
		if (i == 0)
			add_token(a, ft_strdup(""));
		else if (is_special_char(a, i - 1))
			add_token(a, ft_strdup(""));
	}
}

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

int	check_file_redirection(t_data *a, char *file, int *check)
{
	if (!ft_strncmp(file, ">", 2))
		red_flag("minishell: syntax error near unexpected token '>'");
	else if (!ft_strncmp(file, ">>", 3))
		red_flag("minishell: syntax error near unexpected token '>>'");
	else if (!ft_strncmp(file, "<", 2))
		red_flag("minishell: syntax error near unexpected token '<'");
	else if (!ft_strncmp(file, "<<", 3))
		red_flag("minishell: syntax error near unexpected token '<<'");
	if (!ft_strncmp(file, ">", 2) || !ft_strncmp(file, ">>", 3)
		|| !ft_strncmp(file, "<", 2) || !ft_strncmp(file, "<<", 3))
	{
		a->last_ret = 258;
		*check = 1;
		return (1);
	}
	else
		return (0);
}
