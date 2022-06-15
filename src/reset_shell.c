/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/15 16:52:20 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_shell(t_data *a, char **env)
{	
	ft_bzero(a, sizeof(t_data));
	a->env = env_into_list(env);
	a->prompt = get_prompt();
}
