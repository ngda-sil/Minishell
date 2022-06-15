/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:49 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/15 16:42:13 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	t_data	a;

	init_signals(&a);
	while (1)
	{
		reset_shell(&a, env);
		a.line = readline(a.prompt);
		if (!a.line)
			break;
		if (a.line && a.line[0] != '\0')
		{	
			add_history(a.line);
			parsing(&a);
			execution(&a);
		}
		free(a.prompt);
		a.prompt = NULL;
		free(a.line);
		a.line = NULL;
	}
	return (0);
}
