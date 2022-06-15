/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:49 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/15 17:03:43 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_data	a;

	if (ac == 1)
	{
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
				//parsing(&a);
				//execution(&a);
			}
			free(a.prompt); // fonction free_all ? 
			a.prompt = NULL;
			free(a.line);
			a.line = NULL;
		}
		rl_clear_history();
	}
	while (1);
	return (0);
}
