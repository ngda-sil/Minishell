/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:49 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/18 21:05:35 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	a;

	(void)av;
	ft_bzero(&a, sizeof(t_data));
	if (ac == 1)
	{
		init_signals(&a);
		while (1)
		{
			reset_shell(&a, env);
			a.line = readline(a.prompt);
			if (!a.line)
				break ;
			if (a.line && a.line[0] != '\0')
			{	
				add_history(a.line);
				if (parsing(&a))
					continue ;
				execution(&a);
			}
		}
		rl_clear_history();
		free_all(&a);
	}
	return (0);
}
